# === Makefile for iterator testing ===
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g3

SRC = test_iterators.cpp \
      Plant.cpp \
      Bed.cpp \
      Greenhouse.cpp \
      PlantBedIterator.cpp \
      PlantStateIterator.cpp \
      FlyweightSKUIterator.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = test_iterators

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
