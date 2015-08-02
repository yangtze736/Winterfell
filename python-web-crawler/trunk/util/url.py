# Author: hezhijian
# Email: hezhijian1985@gmail.com
'''
        Provide some basic processes for input url.
        a. remove ./ and ../
'''

import urlparse

def process_dotslash(url):
        scheme, netloc, path, query, fragment = urlparse.urlsplit(url)
        if path.find('/../') == -1 and path.find('/./') == -1:
                return url
        
        # process /../ path.
        while True:
                pos = path.find('/../')
                if pos == -1:
                        break
                # netloc/../index.htm
                if pos == 0:
                        path = path[3:]
                else:
                        former_path = path[0:pos]
                        r_slash = former_path.rfind('/')
                        path = path[0:r_slash] + path[pos + 3:]

        # process /./ path.
        while True:
                pos = path.find('/./')
                if pos == -1:
                        break
                path = path[0:pos] + path[pos + 2:]
        return urlparse.urlunsplit((scheme, netloc, path, query, fragment))

# test & sample.
if __name__ == "__main__":
        print process_dotslash("http://www.demo.com/../1/../2/3/4/../5/././6/./index.html")
# Author: hezhijian
# Email: hezhijian1985@gmail.com
'''
        Provide some basic processes for input url.
        a. remove ./ and ../
'''

import urlparse

def process_dotslash(url):
        scheme, netloc, path, query, fragment = urlparse.urlsplit(url)
        if path.find('/../') == -1 and path.find('/./') == -1:
                return url
        
        # process /../ path.
        while True:
                pos = path.find('/../')
                if pos == -1:
                        break
                # netloc/../index.htm
                if pos == 0:
                        path = path[3:]
                else:
                        former_path = path[0:pos]
                        r_slash = former_path.rfind('/')
                        path = path[0:r_slash] + path[pos + 3:]

        # process /./ path.
        while True:
                pos = path.find('/./')
                if pos == -1:
                        break
                path = path[0:pos] + path[pos + 2:]
        return urlparse.urlunsplit((scheme, netloc, path, query, fragment))

# test & sample.
if __name__ == "__main__":
        print process_dotslash("http://www.demo.com/../1/../2/3/4/../5/././6/./index.html")
