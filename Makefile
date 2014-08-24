CC = gcc
AR = ar

all: lib

lib: 
	$(CC) -c varint.c -o varint.o
	$(AR) rcs varint.a varint.o

clean:
	rm *.o
