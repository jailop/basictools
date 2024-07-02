CFLAGS = -Wall -ansi -pedantic

all: libcstring.so

cstring.o: cstring.c cstring.h
	$(CC) -c -Wall -Werror -fpic cstring.c

libcstring.so: cstring.o
	$(CC) -shared -o libcstring.so cstring.o

install:
	cp libcstring.so /usr/local/lib
	cp cstring.h /usr/local/include

clean:
	rm -f cstring.o
	rm -f libcstring.so
