#
# PROGRAM:    Assignment 12
# PROGRAMMER: David Flowers
# LOGON ID:   z1942130
# DATE DUE:   05 05 2022
#

# Compiler Variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

# Rule to link object code files to create executable file
assign12: assign12.o shape.o circle.o rectangle.o triangle.o
	$(CXX) $(CXXFLAGS) -o assign12 $^

# Rules to compile source code file to object code
assign12.o: assign12.cpp shape.h circle.h rectangle.h triangle.h
shape.o: shape.cpp shape.h
circle.o: circle.cpp circle.h
rectangle.o: rectangle.cpp rectangle.h
triangle.o: triangle.cpp triangle.h

# Pseudo-target to remove object code and executable files
clean:
	rm -f assign12 *.o