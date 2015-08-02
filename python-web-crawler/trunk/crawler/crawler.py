# Author: Yunqiao Zhang
# Email: zhangyunqiao@gmail.com

'''
A crawler process which is used to crawling a url. 
'''

# Config.

# Maximum HTTP request waiting time.
MAX_HTTP_REQUEST_TIME = 3 

# Maximum response page size 512K.
MAX_PAGE_SIZE = 2**19

# Maximum request time. If request takes longer than this, don't add this crawler back to available, wait to be killed. This can
# eliminate a race condition.
MAX_REQUEST_TIME = 150

# Retry number.
MAX_RETRY = 2

import Queue as Q
from multiprocessing import Process, Queue
import urllib2

from util.timing import Timing
from util.decorator import Retry
import share

class Crawler(Process):
        def __init__(self, id, GPR, crawlers_queue):
                Process.__init__(self)
                self.id = id
                self.GPR = GPR
                # Making a queue only contains 1 element.
                self.__queue = Queue(1)
                self.__crawlers_queue = crawlers_queue

        def add_request(self, request):
                '''
                Add a request to crawler to crawl. This method is a non-blocking method.
                Return True if succeed, False if failed. 
                NOTE: It should be always TRUE because when scheduler decide to add a request
                to crawler, it's scheduler's reponsibility to find out whether this crawler 
                is available.
                '''
                try:
                        self.__queue.put_nowait(request)
                except Q.Full:
                        return False
                else:
                        return True

        def run(self):
                while True:
                        request = self.__queue.get()

                        # Timing
                        t = Timing()
                        type = None
                        end_url = None
                        headers = None
                        content = None

                        with t:
                                # Urlopen.
                                try:
                                        content, end_url, headers, type = self._send_request(request)
                                        if len(content) == MAX_PAGE_SIZE:
                                                type = share.SIZE_LIMIT_ERROR
                                                content = 'Page size exceeds maximum!'
                                except urllib2.HTTPError as e:
                                        print 'HTTPERROR', e
                                        type = e.code
                                        content = str(e)
                                        headers = e.headers.dict
                                except urllib2.URLError as e:
                                        print 'URLError', e
                                        content = str(e)
                                        if content.find('timed out') != -1:
                                                type = share.TIMEOUT_ERROR
                                        elif content.find('unknown url type') != -1:
                                                type = share.URL_PARSE_ERROR
                                        elif content.find('getaddrinfo failed') != -1:
                                                type = share.DNS_ERROR
                                        else:
                                                type = share.UNKOWN_ERROR
                                        
                                except ValueError as e:
                                        print 'Value Error', e
                                        type = share.URL_PARSE_ERROR
                                        content = str(e)
                                except:
                                        # Catch all errors.
                                        print 'Unkown error'
                                        raise
                                        type = share.UNKOWN_ERROR
                                        content = 'Unkown Error'
                        print t

                        self.GPR.put((type, self.name, t.Timing, request, end_url, headers, content))

                        if t.Timing < MAX_REQUEST_TIME:
                                # Add itself to crawlers_queue to tell scheduler I'm ready to do the next job.
                                self.__crawlers_queue.put(self.id)
        
        @Retry(MAX_RETRY)
        def _send_request(self, request, retry):
                print '[', self.name, ']', ' opening:', request
                response = urllib2.urlopen(request, timeout=MAX_HTTP_REQUEST_TIME)
                print 'reading...'
                content = response.read(MAX_PAGE_SIZE)
                end_url = response.url
                headers = response.headers.dict
                type = response.getcode()
                print 'complete!'
                return content, end_url, headers, type

        



# Unit test & sample usage.
if __name__ == '__main__':
        # Generate a crawlers queue.
        crawlers_queue = Queue(2) 
        crawlers_queue.put(0)
        crawlers_queue.put(1)

        # Generate crawlers.
        crawlers = [Crawler(i, share.GPR, crawlers_queue) for i in range(2)]

        # Start all crawlers.
        map(lambda c:c.start(), crawlers)

        # Get a free crawler.
        id = crawlers_queue.get()
        print id
        crawlers[id].add_request('http://www.google.com/?x=3')

        id = crawlers_queue.get()
        # Get the second crawler.
        print id
        crawlers[id].add_request('http://www.google.com/')

        # qsize should be 0
        print 'Queue size:', crawlers_queue.qsize()

        import time
        time.sleep(5)

        # qsize should be 2 if crawler finished after 5s.
        print 'Queue size:', crawlers_queue.qsize()

        print share.GPR.qsize()

        # Get result from GPR
        result = share.GPR.get()
        print 'result1:', result

        result = share.GPR.get()
        print 'result1:', result

        # Wait for all crawler end.
        map(lambda c:c.join(), crawlers)
