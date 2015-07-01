all : func

func :
	g++ -O2 main.cpp func.cpp urlhandle.cpp -o owmain -lcrypto -DFUNC

perf :
	g++ -O2 main.cpp perf.cpp urlhandle.cpp -o owmain -lcrypto -DPERF

exce :
	g++ -O2 main.cpp exce.cpp urlhandle.cpp -o owmain -lcrypto -DEXCE

# Housekeeping
.PHONY : clean
clean :
	rm -fr *.o *.so owmain
