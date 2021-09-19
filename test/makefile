CXX=g++
CFLAGS=-std=c++11 -g -W -O3
INC=-I../
LIB=-L../ -Wl,-rpath=../ -l_freecplus

all:testcdir testFactor

testcdir: testcdir.cpp
	$(CXX) $(CFLAGS) -o testcdir testcdir.cpp $(INC) $(LIB)

testFactor: testFactor.cpp
	$(CXX) $(CFLAGS) -o testFactor testFactor.cpp $(INC) $(LIB)

clean:
	rm -f testcdir testFactor
