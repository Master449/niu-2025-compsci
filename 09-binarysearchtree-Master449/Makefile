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

all: bst

bst: bst.cc binarysearchtree.h btree.h node.h
	g++ $(CXXFLAGS) -o bst bst.cc 

clean:
	rm -f bst

world: clean all
