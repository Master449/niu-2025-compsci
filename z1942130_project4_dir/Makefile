CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = z1942130_project4
SOURCE = z1942130_project4.cpp
CURRENT_DIR = $(notdir $(shell pwd))

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm $(TARGET)

# Create tar for turn in
zip: clean
	cd ..; tar -cvvf $(TARGET).tar $(CURRENT_DIR); cd $(CURRENT_DIR); mv ../$(TARGET).tar .

.PHONY: clean

