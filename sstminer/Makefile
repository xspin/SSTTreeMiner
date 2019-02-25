AR = ar
CXX = g++

C_FLAGS = -g -std=c++11 -Wno-deprecated

platform=
WINCXX = i686-w64-mingw32-g++
ifeq ($(platform),win)
	CXX=$(WINCXX)
	OPTS = -DWIN
	C_FLAGS = -g -std=c++11 $(OPTS)
endif

INCLUDE_PATH = 

LIB_FLAGS = -L../treeminer/libtreeminer
LIB_treeminer = ../treeminer/libtreeminer.a


LIB = $(LIB_treeminer)

CCSRC = sstminer.cc
HEAD = sstminer.h

CCOBJ = $(CCSRC:.cc=.o)
CPPOBJ = $(CPPSRC:.cc=.o)

OBJS = $(CCOBJ)

TARGET = libsstminer.a

all: $(TARGET) test

fuck:
	echo $(CCSRC)

rb: rebuild

rebuild: clean all

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

test: $(CCOBJ) $(LIB) test.cc
	$(CXX) $(C_FLAGS) -o $@ $^ $(LIB_FLAGS) 

$(CCOBJ): $(HEAD) $(CCSRC)
	$(CXX) $(C_FLAGS) -c -o $*.o $(INCLUDE_PATH) $*.cc

$(LIB_treeminer):
	@cd ../treeminer && $(MAKE)

clean:
	-rm -f $(CCOBJ) $(TARGET) ./test