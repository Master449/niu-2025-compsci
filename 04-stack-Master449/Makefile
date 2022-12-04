#*************************************************************************
#
#	David Flowers II
#	Z1942130
#	CSCI 340 - 0004
#
#	I certify that this is my own work and where appropriate an extension 
#	of the starter code provided for the assignment.
#
#*************************************************************************
CXXFLAGS+=-std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: stack

stack: main.cc stack.h
	g++ $(CXXFLAGS) -o stack main.cc rational.cc

clean:
	rm -f stack

world: clean all