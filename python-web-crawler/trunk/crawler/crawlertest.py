# Author: Yunqiao Zhang
# Email: zhangyunqiao@gmail.com

from scheduler import CrawlerScheduler
import share
import time

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
        while True:
                r = share.GPR.get(block=False)
                print r[0], r[1], r[2], r[3], r[4]
                fp = open(str(n) + '.html', 'w')
                fp.write(r[6])
                fp.close()
                n += 1

        cs.join()
