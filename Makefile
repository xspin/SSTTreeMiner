
CXX = g++
C_FLAGS = -g -std=c++11 

platform=
WINCXX = i686-w64-mingw32-g++
ifeq ($(platform),win)
	CXX=$(WINCXX)
	OPTS = -DWIN
	C_FLAGS = -g -std=c++11 $(OPTS)
	MAKEOPT = platform=win
endif


BIN_PATH = bin
INCLUDE_PATH = 

# LIB_FLAGS = -L./tinyxml2/libtinyxml2 -L./treeminer/libtreeminer -L./sstminer/libsstminer
LIB_tinyxml = tinyxml2/libtinyxml2.a
ifeq ($(platform),win)
	LIB_tinyxml = tinyxml2/libwintinyxml2.a
endif
LIB_treeminer = treeminer/libtreeminer.a
LIB_sstminer = sstminer/libsstminer.a
LIBS = $(LIB_tinyxml) $(LIB_treeminer) $(LIB_sstminer)
LIB_FLAGS = $(addprefix -L./,$(LIBS))

LIB = $(LIB_tinyxml) $(LIB_treeminer) $(LIB_sstminer)

CCSRC = miner.cc
HEAD = miner.h xmlprocess.h

CCOBJ = $(CCSRC:.cc=.o) 
CPPOBJ = $(CPPSRC:.cc=.o)

TEST_SRC = test.cc
TEST_HEAD = 
TEST_OBJ = $(TEST_SRC:.cc=.o)

MINER = $(BIN_PATH)/miner 
TEST = $(BIN_PATH)/test
ifeq ($(platform),win)
	MINER = $(BIN_PATH)/miner.exe 
	TEST = $(BIN_PATH)/test.exe
endif

all: $(MINER) $(TEST)

rb: rebuild

rebuild: clean all

$(TEST): $(TEST_OBJ) $(LIB)
	$(CXX) -o $@ $^ $(LIB_FLAGS)  $(C_FLAGS) 

$(TEST_OBJ): $(TEST_SRC) $(TEST_HEAD)
	$(CXX) -c $*.cc -o $*.o $(INCLUDE_PATH) $(C_FLAGS)

$(MINER): $(CCOBJ) $(LIB) 
	$(CXX) -o $@ $^ $(LIB_FLAGS)  $(C_FLAGS) 

$(LIB_tinyxml):
	@cd tinyxml2 && $(MAKE) $(MAKEOPT)

$(LIB_treeminer): ./treeminer
	@cd treeminer && $(MAKE) $(MAKEOPT)

$(LIB_sstminer): ./sstminer
	@cd sstminer && $(MAKE) $(MAKEOPT)

$(CCOBJ): $(HEAD) $(CCSRC)
	$(CXX) -c $*.cc -o $*.o $(INCLUDE_PATH) $(C_FLAGS)


clean:
	-rm -f *.o $(TARGET) 
	# -rm -f ${BIN_PATH}/*

deepclean: clean
	@cd tinyxml2 && $(MAKE) clean
	@cd treeminer && $(MAKE) clean
	@cd sstminer && $(MAKE) clean