CXXFLAGS = -Wall -g `curl-config --cflags`
LDLIBS = `curl-config --libs`

all: librequest.so request_test

request.o: request.cpp request.h
	$(CXX) -g -c -Wall -fpic request.cpp

request_test: request_test.cpp request.o
	$(CXX) -Wall -p -g `curl-config --cflags --libs` -lboost_unit_test_framework request_test.cpp request.o -o request_test

librequest.so: request.o
	$(CXX) -shared -o librequest.so request.o

install:
	cp librequest.so /usr/local/lib
	cp request.h /usr/local/include

clean:
	rm -f *.o
	rm -f *.so
