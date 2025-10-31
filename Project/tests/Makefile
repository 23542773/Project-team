# Makefile for doctest unit tests
# Usage: make all (compile all tests)
#        make run (compile and run all tests)
#        make clean (remove executables)

CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES = -I"../Prototype" -I"../Flyweight" -I"../Strategy" -I"../State (with Singleton)" -I..

# Directories (no quotes in variable definitions)
# All pattern files are in the parent directory
PATTERN_DIR = ..

# State Pattern Files
STATE_SOURCES = $(PATTERN_DIR)/Plant.cpp \
                $(PATTERN_DIR)/SeedlingState.cpp \
                $(PATTERN_DIR)/GrowingState.cpp \
                $(PATTERN_DIR)/MatureState.cpp \
                $(PATTERN_DIR)/WiltingState.cpp \
                $(PATTERN_DIR)/DeadState.cpp

# Strategy Pattern Files
STRATEGY_SOURCES = $(PATTERN_DIR)/Plant.cpp \
                   $(PATTERN_DIR)/DesertStrategy.cpp \
                   $(PATTERN_DIR)/TropicalStrategy.cpp \
                   $(PATTERN_DIR)/IndoorStrategy.cpp \
                   $(PATTERN_DIR)/MediterraneanStrategy.cpp \
                   $(PATTERN_DIR)/WetlandStrategy.cpp

# Flyweight Pattern Files
FLYWEIGHT_SOURCES = $(PATTERN_DIR)/SpeciesCatalog.cpp \
                    $(PATTERN_DIR)/SpeciesFlyweight.cpp \
                    $(PATTERN_DIR)/UnsharedSpeciesFlyweight.cpp

# Test executables
TEST_STATE = test_state.exe
TEST_STRATEGY = test_strategy.exe
TEST_FLYWEIGHT = test_flyweight.exe

# Default target
all: $(TEST_STATE) $(TEST_STRATEGY) $(TEST_FLYWEIGHT)

# Compile State Pattern tests
$(TEST_STATE): test_state.cpp
	@echo "Compiling State Pattern tests..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) test_state.cpp \
		"$(PATTERN_DIR)/Plant.cpp" \
		"$(PATTERN_DIR)/SeedlingState.cpp" \
		"$(PATTERN_DIR)/GrowingState.cpp" \
		"$(PATTERN_DIR)/MatureState.cpp" \
		"$(PATTERN_DIR)/WiltingState.cpp" \
		"$(PATTERN_DIR)/DeadState.cpp" \
		"$(PATTERN_DIR)/SpeciesFlyweight.cpp" \
		"$(PATTERN_DIR)/UnsharedSpeciesFlyweight.cpp" \
		"$(PATTERN_DIR)/SoilMix.cpp" \
		"$(PATTERN_DIR)/Pot.cpp" \
		-o $(TEST_STATE)
	@echo "State tests compiled successfully!"

# Compile Strategy Pattern tests
$(TEST_STRATEGY): test_strategy.cpp
	@echo "Compiling Strategy Pattern tests..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) test_strategy.cpp \
		"$(PATTERN_DIR)/Plant.cpp" \
		"$(PATTERN_DIR)/DesertStrategy.cpp" \
		"$(PATTERN_DIR)/TropicalStrategy.cpp" \
		"$(PATTERN_DIR)/IndoorStrategy.cpp" \
		"$(PATTERN_DIR)/MediterraneanStrategy.cpp" \
		"$(PATTERN_DIR)/WetlandStrategy.cpp" \
		"$(PATTERN_DIR)/SpeciesFlyweight.cpp" \
		"$(PATTERN_DIR)/UnsharedSpeciesFlyweight.cpp" \
		"$(PATTERN_DIR)/SoilMix.cpp" \
		"$(PATTERN_DIR)/Pot.cpp" \
		-o $(TEST_STRATEGY)
	@echo "Strategy tests compiled successfully!"

# Compile Flyweight Pattern tests
$(TEST_FLYWEIGHT): test_flyweight.cpp
	@echo "Compiling Flyweight Pattern tests..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) test_flyweight.cpp \
		"$(PATTERN_DIR)/SpeciesCatalog.cpp" \
		"$(PATTERN_DIR)/SpeciesFlyweight.cpp" \
		"$(PATTERN_DIR)/UnsharedSpeciesFlyweight.cpp" \
		-o $(TEST_FLYWEIGHT)
	@echo "Flyweight tests compiled successfully!"

# Run all tests
run: all
	@echo ""
	@echo "=========================================="
	@echo "Running State Pattern Tests..."
	@echo "=========================================="
	./$(TEST_STATE)
	@echo ""
	@echo "=========================================="
	@echo "Running Strategy Pattern Tests..."
	@echo "=========================================="
	./$(TEST_STRATEGY)
	@echo ""
	@echo "=========================================="
	@echo "Running Flyweight Pattern Tests..."
	@echo "=========================================="
	./$(TEST_FLYWEIGHT)
	@echo ""
	@echo "All tests completed!"

# Clean executables
clean:
	@echo "Cleaning test executables..."
	rm -f $(TEST_STATE) $(TEST_STRATEGY) $(TEST_FLYWEIGHT)
	@echo "Clean complete!"

# Run only state tests
test-state: $(TEST_STATE)
	@echo "Running State Pattern Tests..."
	./$(TEST_STATE)

# Run only strategy tests
test-strategy: $(TEST_STRATEGY)
	@echo "Running Strategy Pattern Tests..."
	./$(TEST_STRATEGY)

# Run only flyweight tests
test-flyweight: $(TEST_FLYWEIGHT)
	@echo "Running Flyweight Pattern Tests..."
	./$(TEST_FLYWEIGHT)

.PHONY: all run clean test-state test-strategy test-flyweight
