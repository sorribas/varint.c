CC = gcc
AR = ar

all: lib

lib: 
	$(CC) -c varint.c -o varint.o
	$(AR) rcs varint.a varint.o

clean:
	rm *.o

test:
	$(CC) test/main.c varint.a -o test/main
	./test/main

.PHONY: test
