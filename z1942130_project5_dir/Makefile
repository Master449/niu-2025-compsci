CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = z1942130_project5
SOURCE = z1942130_project5.cpp
CURRENT_DIR = $(notdir $(shell pwd))

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) -lpthread

clean:
	rm $(TARGET)

# Create tar for turn in
zip: clean
	cd ..; tar -cvvf $(TARGET).tar $(CURRENT_DIR); cd $(CURRENT_DIR); mv ../$(TARGET).tar .

build:
	make && ./$(TARGET) tiny.txt

debug:
	$(CXX) -g $(CXXFLAGS) $(SOURCE) -o $(TARGET)

.PHONY: clean

