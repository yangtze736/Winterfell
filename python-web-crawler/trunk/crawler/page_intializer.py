# Author: Yunqiao Zhang
# Email: zhangyunqiao@gmail.com

import share
import Queue as Q
from util.canonicalizer import canonicalize

class PageInitializer(object):
        def __init__(self, GPR):
                self._GPR = GPR
        
        def get_page(self):
                try:
                        type, pid, time, iu, eu, headers, content = self._GPR.get(block=False)
                except Q.Empty:
                        return (None, None)

                # Ignore errors first.
                if type == share.OK:
                        eu = canonicalize(eu) 
                        return eu, content
                else:
                        print "Error Code: ", type, "Message:", content
                        return (None, None)
