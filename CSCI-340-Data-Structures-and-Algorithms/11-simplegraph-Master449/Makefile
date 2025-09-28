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

all: graph

graph: simplegraph.cc graph.h
	g++ $(CXXFLAGS) -o simplegraph simplegraph.cc graph.cc

clean:
	rm -f graph

world: clean all
