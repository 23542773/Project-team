CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../include

# Core files needed for iterator pattern testing
CORE_SRC = \
    ../src/Plant.cpp \
    ../src/Bed.cpp \
    ../src/Greenhouse.cpp \
    ../src/PlantBedIterator.cpp \
    ../src/GreenhouseIterator.cpp

# State pattern files (needed for Plant dependencies)
STATE_SRC = \
    ../src/SeedlingState.cpp \
    ../src/GrowingState.cpp \
    ../src/MatureState.cpp \
    ../src/WiltingState.cpp \
    ../src/DeadState.cpp

# Strategy pattern files (needed for Plant dependencies)  
STRATEGY_SRC = \
    ../src/DesertStrategy.cpp \
    ../src/TropicalStrategy.cpp \
    ../src/IndoorStrategy.cpp \
    ../src/MediterraneanStrategy.cpp \
    ../src/WetlandStrategy.cpp

# Flyweight files (needed for Plant dependencies)
FLYWEIGHT_SRC = \
    ../src/SpeciesFlyweight.cpp \
    ../src/UnsharedSpeciesFlyweight.cpp \
    ../src/SpeciesCatalog.cpp \
    ../src/SpeciesKey.cpp

# Combine all source files
SRC_FILES = $(CORE_SRC) $(STATE_SRC) $(STRATEGY_SRC) $(FLYWEIGHT_SRC)

# Iterator tests
test_main: IteratorTest.cpp $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

runIt: test_main
	./test_main

# Flyweight tests - only need flyweight-related files
flyweight_test: FlyWeightTest.cpp $(FLYWEIGHT_SRC)
	$(CXX) $(CXXFLAGS) $^ -o flyweight_test

runFly: flyweight_test
	./flyweight_test

clean:
	rm -f test_main flyweight_test

.PHONY: runIt runFly clean