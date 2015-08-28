# C++ Client Makefile
BUILD_LEVEL ?= DEBUG

# if you create new source folder(include cpp) please add to below like
VPATH = src
HOME=/usr/local/middleware

# if you have new inc folder need to input, add in below like
INCLUDE +=\
          -I ./include \

#CFLAGS= -g -O2 $(INCLUDE) -gstabs -Wno-write-strings -Werror -fPIC -shared -std=c++0x
ifeq ($(strip $(BUILD_LEVEL)), RELEASE)
	CFLAGS= -g -O2 $(INCLUDE) -gstabs -Wno-write-strings -Werror -fPIC -shared -std=c++0x -DRELEASE
endif
ifeq ($(strip $(BUILD_LEVEL)), DEBUG)
	CFLAGS= -g -O0 $(INCLUDE) -gstabs -Wno-write-strings -Werror -fPIC -shared -std=c++0x -DDEBUG
endif

CC = g++

# if you have new lib need to link, add in below like
LIBSECRYPTO=$(HOME)/lib/libsecrypto.so
LIB+=-L. -lz -lcurl -lrt -lcrypto -lssl -lstdc++ -lpthread $(LIBSECRYPTO)

LIB_FLAGS = -fPIC -shared

# need *.o to generate test_client
LIB_MIDDLEWARE = libmiddleware.so

LIB_DEP = baseFunc.o \
		  static.o \
		  trap.o \
		  configure.o \
		  urlhandle.o \
		  iceGrid.o \
		  parser.o \
		  mfcFile.o \
		  perform.o \
		  fileTransfer.o \

all: check $(LIB_MIDDLEWARE) clear

check:
	cd lib/ && tar zxvf libdependent_centos.tar.gz
	if [ ! -d $(HOME)/lib ];then mkdir -p $(HOME)/lib;fi
	cp -rf lib/* $(HOME)/lib

clear:
	rm -fr lib/lib*.so*
	cp -rf $(LIB_MIDDLEWARE) $(HOME)/lib/
	mv -f $(LIB_MIDDLEWARE) lib/
	rm -fr *.o

clean:
	rm -fr lib/$(LIB_MIDDLEWARE)

log:
	git log '--pretty=format:%ad %s' --date=short > Changelog

# the rule how to make *.o
.c.o:
	$(CC) -c $(CFLAGS) $<

.cpp.o:
	$(CC) -c $(CFLAGS) $<

$(LIB_MIDDLEWARE): $(LIB_DEP)
	$(CC) -o $(LIB_MIDDLEWARE) $(LIB_DEP) $(LIB_FLAGS) $(LIB)

dep:
	$(CC) -MM *.c *.cpp


# describe how many file the .o file needed to build
baseFunc.o:src/baseFunc.cpp include/baseFunc.h
static.o:src/static.cpp include/static.h
trap.o:src/trap.cpp include/trap.h
configure.o:src/configure.cpp include/configure.h
urlhandle.o:src/urlhandle.cpp include/urlhandle.h
iceGrid.o:src/iceGrid.cpp include/iceGrid.h
parser.o:src/parser.cpp include/parser.h
mfcFile.o:src/mfcFile.cpp include/mfcFile.h
perform.o:src/perform.cpp include/perform.h
fileTransfer.o:src/fileTransfer.cpp include/fileTransfer.h
