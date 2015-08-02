# Author: Zhijian He
# Email: hezhijian1985@gmail.com

'''
Implement a component used to score for a url.
'''

PERFECT_PAGE = 100
HIGHQUALITY_PAGE = 60
LOWQUALITY_PAGE = 59
NOTSCORED_PAGE = -1


import urlparse
import threading

source_sitelist = []
source_sitelist_RLock = threading.RLock()

def __produce_source_sitelist():
        '''
        It imports the websites from 'coupon site.txt' file,
        and stores all the sites' netloc+path hash value into a list,
        in the future, only those urls whose netloc+path hash value belong
        to the list can will ranked with high score.
        '''
        if len(source_sitelist) > 0:
                return
        source_sitelist_RLock.acquire()
        if len(source_sitelist) > 0:
                return
        for url in open('coupon site.txt', 'r'):
                scheme, netloc, path, query, fragment = urlparse.urlsplit(url)
                source_sitelist.append(hash(netloc + __rm_path_slash(path)))
        source_sitelist.sort()
        source_sitelist_RLock.release()

def __rm_path_slash(path):
        path_start = 0
        # decrease 2 is because of the end of path is '\n'
        path_end = len(path) - 2
        if len(path) >= 1:
                if path[0] == '/':
                        if len(path) > 1:
                                path_start = 1
                        else:
                                return ""
                if path[path_end] == '/':
                        path_end -= 1
                        return path[path_start:path_end + 1]
        return path[path_start:path_end + 1]

def score(link):
        if len(source_sitelist) <= 0:
                __produce_source_sitelist()
        if len(source_sitelist) <= 0:
                return NOTSCORED_PAGE
        scheme, netloc, path, query, fragment = urlparse.urlsplit(link)
        hashurl = hash(netloc + __rm_path_slash(path))
        low = 0
        high = len(source_sitelist) - 1
        i = (low + high) / 2
        while low <= high:
                if hashurl == source_sitelist[i]:
                        return HIGHQUALITY_PAGE
                elif hashurl > source_sitelist[i]:
                        high = i - 1
                else:
                        low = i + 1
                i = (low + high) / 2
        return LOWQUALITY_PAGE

# Unit test & sample usage.
if __name__ == '__main__':
        print score('http://www.sina.com.cn')
