all: lib_freecplus.a lib_freecplus.so

lib_freecplus.a:_freecplus.h _freecplus.cpp
	g++ -c -o lib_freecplus.a _freecplus.cpp

lib_freecplus.so:_freecplus.h _freecplus.cpp
	g++ -fPIC -shared -o lib_freecplus.so _freecplus.cpp


clean:
	rm -f lib_freecplus.a lib_freecplus.so
