#*************************************************************************
#
#	David Flowers II
#	Z1942130
#	CSCI 340 - 0004
#
#	I certify that this is my own work.
#
#*************************************************************************
OBJS	= hashmain.o
SOURCE	= hashmain.cc htable.cc
HEADER	= entry.h hashmain.h htable.h
OUT	= hash
CC	= g++ -std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) htable.cc

hashmain.o: hashmain.cc htable.cc
	$(CC) -c hashmain.cc htable.cc

clean:
	rm -f hash *.o
