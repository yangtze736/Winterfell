import urlparse

def canonicalize(url):
        # lowercase.
        url = url.lower()

        scheme, netloc, path, query, fragment = urlparse.urlsplit(url)

        slash_pos = path.rfind('/')
        dot_pos = path.rfind('.')
        if slash_pos >= dot_pos and (len(path) == 0 or path[-1] != '/'):
                # end dir with slash.
                path += '/'
        elif slash_pos < dot_pos:
                # remove default.
                filename = path[slash_pos + 1: dot_pos]
                if filename == 'default' or filename == 'index':
                        path = path[0: slash_pos + 1]
        
        # sort queries.
        params = urlparse.parse_qsl(query)
        params.sort()
        query = '&'.join('%s=%s' % x for x in params)

        # Remove fragment also
        return urlparse.urlunsplit((scheme, netloc, path, query, ''))


if __name__ == '__main__':
        print canonicalize('HTTP://WWW.EXAMPLE.COM')
        print canonicalize('http://www.example.com/test.htm?c=1&b=2&a=3')
        print canonicalize('http://www.example.com/demo')
        print canonicalize('http://www.example.com/index.html')
        print canonicalize('http://www.example.com/index.html?a=1')
        print canonicalize('http://www.example.com/demo.html?')
