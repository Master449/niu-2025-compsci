CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = z1942130_project1
SOURCE = z1942130_*.cpp
CURRENT_DIR = $(notdir $(shell pwd))

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

# Create file to hand in
zip: clean
	cd ..; tar -cvvf $(TARGET).tar $(CURRENT_DIR); cd $(CURRENT_DIR)
	mv ../$(TARGET).tar .

.PHONY: clean
