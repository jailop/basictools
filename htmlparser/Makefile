BINS = htmlparser_test
LIBS = libhtmlparser.so

all: $(BINS) $(LIBS)

htmlparser.o: htmlparser.h htmlparser.cpp
	$(CXX) -Wall -fpic `xml2-config --cflags` -c htmlparser.cpp 

htmlparser_test: htmlparser_test.cpp htmlparser.o
	$(CXX) -Wall -p -g `xml2-config --cflags --libs` -lboost_unit_test_framework htmlparser_test.cpp htmlparser.o -o htmlparser_test

libhtmlparser.so: htmlparser.o
	$(CC) -shared -o libhtmlparser.so htmlparser.o

install:
	cp libhtmlparser.so /usr/local/lib
	cp htmlparser.h /usr/local/include

clean:
	rm -f *.o
	rm -f $(BINS)
	rm -f $(LIBS)
