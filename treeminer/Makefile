AR = ar
CC = g++
# CFLAGS = -O3 
CFLAGS = -g -std=c++11 -Wno-deprecated

platform=
WINCXX = i686-w64-mingw32-g++
ifeq ($(platform),win)
	CC=$(WINCXX)
	OPTS = -DWIN
	C_FLAGS = -g -std=c++11 $(OPTS)
endif


HDRS = treeminer.h timetrack.h calcdb.h eqclass.h stats.h idlist.h hashtable.h
OBJS = calcdb.o eqclass.o stats.o idlist.o treeminer.o hashtable.o
LIBS = 
TARGET = libtreeminer.a
TEST_LIB_FLAG = -L. -ltreeminer

default: $(TARGET) test

clean:
	rm -rf *.o $(TARGET) 
	rm test

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

test: $(TARGET) test.o
	$(CC) $(CFLAGS) -o $@ $^ $(TEST_LIB_FLAG)

.SUFFIXES: .o .cpp

.cpp.o:
	$(CC) $(CFLAGS) -c $<

test.o: test.cpp 
	$(CC) $(CFLAGS) -c $^ $(TEST_LIB_FLAG)

# dependencies
# $(OBJS): $(HFILES)
treeminer.o: $(HDRS)
calcdb.o: calcdb.h treeminer.h idlist.h
eqclass.o: eqclass.h treeminer.h idlist.h calcdb.h idlist.h
stats.o: stats.h
idlist.o: idlist.h
hashtable.o: hashtable.h treeminer.h eqclass.h