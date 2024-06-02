CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lncurses

all: hello

hello: hello.o
    $(CC) $(LDFLAGS) hello.o -o hello

hello.o: hello.cpp
    $(CC) $(CFLAGS) hello.cpp

clean:
    rm -f hello hello.o
