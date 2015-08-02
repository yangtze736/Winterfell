# Authro: Yunqiao Zhang
# Email: zhangyunqiao@gmail.com

'''
A global page repository (GPR) for both consumers and crawlers.
Data structure stored in GPR is as follows:
Each item is a 7-tuple
(type, pid, time, Initial Url, End Url, Headers, Content).

  *TYPE represents a code defined as follows:
  share.TIMEOUT
  share.URL_PARSE_ERROR
  share.SIZE_LIMIT_ERROR
  share.DNS_ERROR
  share.UNKOWN_ERROR
  share.OK
  type can also be a integer representing the error code returned by HTTP server.

  *pid: The crawler process id.
        *time: How much time used to crawl this page.
  *Initial Url is the url in request.
  *End Url is the final url (the same as initial url if no redirect).
  *Headers: headers returned by HTTP server.
  *Content: Page content or Error message if happened.
'''

TIMEOUT_ERROR = 0
URL_PARSE_ERROR = 1
SIZE_LIMIT_ERROR = 2
DNS_ERROR = 3
UNKOWN_ERROR = 4
OK = 200

from multiprocessing import Queue

# Global Page Repsitory with the capacity of 1K.
GPR = Queue(2**10)
