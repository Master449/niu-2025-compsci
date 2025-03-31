CXX = g++
CXXFLAGS = -Wall -std=c++20

TARGET = z1942130_project5
EC_TARGET = z1942130_project5_p2
SOURCE = z1942130_project5.cpp
EC_SOURCE = z1942130_project5_p2.cpp
CURRENT_DIR = $(notdir $(shell pwd))

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) -lpthread
	$(CXX) $(CXXFLAGS) $(EC_SOURCE) -o $(EC_TARGET) -lpthread

clean:
	rm $(TARGET)
	rm $(EC_TARGET)

# Create tar for turn in
zip: 
	cd ..; tar -cvvf $(TARGET).tar $(CURRENT_DIR); cd $(CURRENT_DIR); mv ../$(TARGET).tar .

build:
	make && ./$(TARGET) tiny.txt

debug:
	$(CXX) -g $(CXXFLAGS) $(SOURCE) -o $(TARGET)

.PHONY: clean

