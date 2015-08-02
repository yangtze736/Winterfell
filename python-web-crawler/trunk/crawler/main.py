# Author: Yunqiao Zhang
# Email: zhangyunqiao@gmail.com

from scheduler import CrawlerScheduler
import share
import time
from page_intializer import PageInitializer

if __name__ == '__main__':
        cs = CrawlerScheduler(share.GPR)
        cs.start()

        for line in open("test.txt", 'r'):
                line = line.strip()
                cs.add_request(line)
        
        time.sleep(40) 

        print 'size:', share.GPR.qsize()
        # Get content out
        n = 0
        
        pi = PageInitializer(share.GPR)
        while True:
                url, content = pi.get_page()
                fp = open(str(n) + '.html', 'w')
                if url != None:
                        fp.write(content)
                fp.close()
                n += 1

        cs.join()
