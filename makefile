BIN=board.exe
CXXFLAGS=-std=c++11

SRCS = board.cpp 

OBJS =  $(SRCS:.cpp=.o)

default : $(BIN)

$(BIN) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LLDLIBS)
