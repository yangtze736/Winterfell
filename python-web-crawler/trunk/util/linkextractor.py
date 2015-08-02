# Author: Zhijian He
# Email: hezhijian1985@gmail.com

'''
Implement a simple linkextractor used to extract page <a> links.

Call func link_extractor(), input is the page url and page content.
Return a links list.

Has processed the <base> tag, what's more relative links are in
consideration.
'''

from sgmllib import SGMLParser
import urlparse
import util.url

class PageParser(SGMLParser):
        '''A simple html parser used to analyze <a> tags.'''
        def __init__(self, pageurl):
                SGMLParser.__init__(self)
                self.pageurl = pageurl
                # this page's current path,
                # i.g. www.demo.com/test/index.html
                # the current_path is www.demo.com/test/
                self.current_path = self.__get_url_dir(pageurl)
                self.base_scheme, self.base_netloc, self.base_path, \
                self.base_query, self.base_fragment     = urlparse.urlsplit(self.current_path)
                # linklist stores the links originated from <a> tags.
                self.linklist = []

        def start_base(self, attrs):
                for name, value in attrs:
                        if name == 'href' and value != None:
                                self.current_path = self.__get_url_dir(value)
                                self.base_scheme, self.base_netloc, self.base_path, \
                                self.base_query, self.base_fragment     = urlparse.urlsplit(self.current_path)

        def start_a(self, attrs):
                for name, link in attrs:
                        if name == 'href' and link != None:
                                link = link.lstrip()
                                if link.find('javascript') == 0:
                                        continue
                                scheme, netloc, path, query, fragment = urlparse.urlsplit(link)
                                if len(scheme) != 0 and scheme != 'http':
                                        continue
                                if len(scheme) != 0 or len(netloc) != 0:
                                        link = util.url.process_dotslash(link)
                                        self.linklist.append(link)
                                        continue
                                elif len(path) != 0:
                                        if path[0] == '/':
                                                link = self.current_path + link[1:]
                                        else:
                                                link = self.current_path + link
                                        link = util.url.process_dotslash(link)
                                        self.linklist.append(link)

        def __get_url_dir(self, url):
                scheme, netloc, path, query, fragment = urlparse.urlsplit(url)
                slash_pos = path.rfind('/')
                dot_pos = path.rfind('.')
                # no path info, like: http://www.demo.com/
                if len(path) == 0 or slash_pos <= 0:
                        return urlparse.urlunsplit((scheme, netloc, '/', '', ''))
                # the path is a page, like: /test/index.html
                if slash_pos < dot_pos:
                        return urlparse.urlunsplit((scheme, netloc, path[:slash_pos] + '/', '', ''))
                elif slash_pos < len(path) - 1:
                        return urlparse.urlunsplit((scheme, netloc, path + '/', '', ''))
                else:
                        return url

def link_extractor(pagecont, pageurl):
        '''
        Extract all the links from a web pagecontent, 
        and to each link, s small pageranker will be applied
        to determine whether this link has high quality, only qualified
        urls will be stored into the return list.
        '''
        qualified_linklist = []
        parser = PageParser(pageurl)
        parser.feed(pagecont)
        import pageranker
        for link in parser.linklist:
                score = pageranker.score(link)
                if score >= pageranker.HIGHQUALITY_PAGE:
                        qualified_linklist.append((link, score))
        return qualified_linklist

# Unit Test & Sample
if __name__ == "__main__":
        import urllib2
        pagecont = urllib2.urlopen('http://www.zhekou4u.com/').read()
        linklist = link_extractor(pagecont, 'http://www.zhekou4u.com/')
        for link in linklist:
                print link
