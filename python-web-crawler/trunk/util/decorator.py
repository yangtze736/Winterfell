# Author: Yunqiao Zhang
# Email: zhangyunqiao@gmail.com
'''
Implement a bunch of useful decorators.
'''


'''
A decorator for singleton pattern. The decorated class must have 
a __init__ without parameters (except self).
'''
def Singleton(cls):
        instances = {}
        def getinstance():
                if cls not in instances:
                        instances[cls] = cls()
                return instances[cls]
        return getinstance



'''
A dcorator that makes auto retry. The decorated function must accept a named 'retry'
parameter to get the current retry times. Retry function only retry n times until the function
doesn't raise an exception. other wise, it will raise the last exception out after n times retry.
'''
class Retry(object):
        def __init__(self, n):
                self.__retry = n
        def __call__(self, f):
                def newf(*parg, **dargs):
                        for i in range(self.__retry):
                                dargs['retry'] = i
                                try:
                                        return f(*parg, **dargs)
                                except:
                                        if i == self.__retry - 1:
                                                raise
                return newf

class B(object):
        @Retry(3)
        def f(self, param, retry):
                print retry
                print param
                if retry == 2:
                        return 10 
                else:
                        raise Exception('retry please')

# Unit Test & Sample.
if __name__ == '__main__':
        @Singleton
        class A(object): pass

        a = A()
        b = A()

        # Compare id. Same?
        print id(a)
        print id(b)

        B().f('param')
