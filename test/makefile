CXX=g++
CFLAGS=-std=c++11 -g -W -O3
INC=-I../
LIB=-Wl,-rpath=../ -l_freecplus

all:testcdir

testcdir: testcdir.cpp
	$(CXX) $(CFLAGS) -o testcdir testcdir.cpp $(INC) $(LIB)

clean:
	rm -f testcdir
