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

all: parking

parking: parking.cc car.h garage.h
	g++ $(CXXFLAGS) -o parking parking.cc 

clean:
	rm -f parking

world: clean all
