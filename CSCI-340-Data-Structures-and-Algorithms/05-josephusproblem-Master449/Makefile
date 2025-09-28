#*************************************************************************
#
#	David Flowers II
#	Z1942130
#	CSCI 340 - 0004
#
#	I certify that this is my own work.
#
#*************************************************************************
CXXFLAGS+=-std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: josephus

josephus: josephus.cc josephus.h
	g++ $(CXXFLAGS) -o josephus josephus.cc 

clean:
	rm -f josephus

world: clean all