# Author: Yunqiao Zhang
# Email: zhangyunqiao@gmail.com

'''
Crawler scheduler:
        * Maintains a large Queue for processing request.
        * When consumer get links from page they will send request to scheduler.
        * Crawler scheduler is reponsible to dispatch request to available crawler process.
        * Crawler will monitor crawler process in effect if any of them is crash, scheduler will make new crawler then.

TODO:
        * If Kill a crawler, put the request back.
        * Don't drop request when queue is full.
'''

# Config.
# Crawler Process Number.
NUMBER_OF_CRAWLERS = 10

# Max waiting time for scheduler to wait for a available crawler process.
MAX_WAITING_TIME = 10

# Max time for a crawler to crawl a page. If crawler process can't respond after his time, it will be killed
# and new crawler process will be generated.
MAX_CRAWL_TIME = 180

# Max waiting time for add a request.
MAX_REQUEST_WAITING_TIME = 1 

import Queue as Q
from multiprocessing import Queue, Process
import datetime

from crawler import Crawler
import share

class CrawlerScheduler(Process):
        def __init__(self, GPR):
                Process.__init__(self)
                self.GPR = GPR
                self.__request_queue = Queue(2**15)
                self.__crawlers_queue = Queue(NUMBER_OF_CRAWLERS)
        
        def add_request(self, request):
                '''
                Add a request to scheduler. Waiting until timeout. In case of timeout, just log it.
                '''
                try:
                        self.__request_queue.put(request, timeout=MAX_REQUEST_WAITING_TIME)
                except Q.Full:
                        print 'Crawlers too busy, drop request:', request


        def run(self):
                # Generate crawler processes.
                print 'Start crawlers processes...'
                self.__crawlers = [Crawler(i, self.GPR, self.__crawlers_queue) for i in range(NUMBER_OF_CRAWLERS)]
                print 'Done.'

                self.__crawlers_record = []
                for i in range(NUMBER_OF_CRAWLERS):
                        # Put crawlers into available queue.
                        self.__crawlers_queue.put(i)
                        # Start crawler job.
                        self.__crawlers[i].start()
                        self.__crawlers_record.append(datetime.datetime.now())

                print 'Ready to accept request.'
                # Start waiting for request and dispatch to crawler process.
                while True:
                        req = self.__request_queue.get()
                                
                        done = False

                        while not done:
                                # Get a avaiable crawler process id.
                                id = None
                                try:
                                        id = self.__crawlers_queue.get(timeout=MAX_WAITING_TIME)
                                        # Reset this crawlers last crawl time.
                                        self.__crawlers_record[id] = datetime.datetime.now()
                                except Q.Empty:
                                        # If no crawler is available.
                                        self._check_crawlers()
                                if not id is None:
                                        self.__crawlers[id].add_request(req)
                                        done = True


        def _check_cralwers(self):
                now = datetime.datetime.now()
                for i in range(NUMBER_OF_CRAWLERS):
                        if (now - self.__crawlers_record[i]).seconds > MAX_CRAWL_TIME:
                                # Kill the crawler and get a new one. 
                                # NOTE: if crawler is killed, the request is lost forever.
                                print "Killing crawler:", i
                                if self.__crawlers[i].is_alive():
                                        try:
                                                self.__crawlers[i].terminate()
                                        except:pass
                                print "Done."
                                print "Starting new crawler."
                                self.__crawlers[i] = Crawler(i, self.GPR, self.__crawlers_queue)
                                self.__crawlers[i].start()
                                self.__crawlers_queue.put(i)
                                self.__crawlers_record[i] = now

if __name__ == '__main__':
        cs = CrawlerScheduler(share.GPR)
        cs.start()
        cs.add_request('http://www.google.com')
        cs.add_request('http://www.google.com/?a=x')
        cs.add_request('http://www.goolerrrr.com/?')
        cs.join()
