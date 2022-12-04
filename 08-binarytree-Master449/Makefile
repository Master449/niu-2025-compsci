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

all: binarytree

binarytree: binarytree.cc btree.h node.h
	g++ $(CXXFLAGS) -o binarytree binarytree.cc 

clean:
	rm -f binarytree

world: clean all
