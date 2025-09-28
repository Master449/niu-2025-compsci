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

all: wordscanner

wordscanner: wordscanner.cc
	g++ $(CXXFLAGS) -o wordscanner wordscanner.cc 

clean:
	rm -f wordscanner

world: clean all
