
CXX = g++

C_FLAGS = -g -std=c++11 


INCLUDE_PATH = 

LIB_FLAGS = -L./tinyxml2/libtinyxml2 -L./treeminer/libtreeminer -L./sstminer/libsstminer
LIB_tinyxml = tinyxml2/libtinyxml2.a
LIB_treeminer = treeminer/libtreeminer.a
LIB_sstminer = sstminer/libsstminer.a

# OBJ_sstminer = sstminer/sstminer.o


LIB = $(LIB_tinyxml) $(LIB_treeminer) $(LIB_sstminer)

CCSRC = $(wildcard *.cc)
CPPSRC = $(wildcard *.cpp)
HEAD = $(wildcard *.h)

CCOBJ = $(CCSRC:.cc=.o) $(OBJ_sstminer)
CPPOBJ = $(CPPSRC:.cc=.o)

TARGET = miner

all: $(TARGET)

fuck:
	echo $(CCSRC)

rb: rebuild

rebuild: clean all

miner: $(CCOBJ) $(LIB) $(OBJ_sstminer)
	$(CXX) -o $@ $^ $(LIB_FLAGS)  $(C_FLAGS) 

$(LIB_tinyxml):
	@cd tinyxml2 && $(MAKE)

$(LIB_treeminer): ./treeminer
	@cd treeminer && $(MAKE)

$(LIB_sstminer): ./sstminer
	@cd sstminer && $(MAKE)

$(CCOBJ): $(HEAD) $(CCSRC)
	$(CXX) -c $*.cc -o $*.o $(INCLUDE_PATH) $(C_FLAGS)

# $(CPPOBJ): $(CPPSRC) 
# 	$(CXX) -c -o $*.o $(INCLUDE_PATH) $(C_FLAGS) $(LIB_FLAGS) $*.cpp

clean:
	-rm -f $(CCOBJ) $(TARGET) 

deepclean: clean
	@cd tinyxml2 && $(MAKE) clean
	@cd treeminer && $(MAKE) clean
	@cd sstminer && $(MAKE) clean