# Makefile for doctest unit tests
# Usage: make all (compile all tests)
#        make run (compile and run all tests)
#        make clean (remove executables)

CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES = -I"../Prototype" -I"../Flyweight" -I"../Strategy" -I"../State (with Singleton)"

# Directories (no quotes in variable definitions)
STATE_DIR = ../State (with Singleton)
STRATEGY_DIR = ../Strategy

# State Pattern Files
STATE_SOURCES = $(STATE_DIR)/Plant.cpp \
                $(STATE_DIR)/SeedlingState.cpp \
                $(STATE_DIR)/GrowingState.cpp \
                $(STATE_DIR)/MatureState.cpp \
                $(STATE_DIR)/WiltingState.cpp \
                $(STATE_DIR)/DeadState.cpp

# Strategy Pattern Files
STRATEGY_SOURCES = $(STRATEGY_DIR)/Plant.cpp \
                   $(STRATEGY_DIR)/DesertStrategy.cpp \
                   $(STRATEGY_DIR)/TropicalStrategy.cpp \
                   $(STRATEGY_DIR)/IndoorStrategy.cpp \
                   $(STRATEGY_DIR)/MediterraneanStrategy.cpp \
                   $(STRATEGY_DIR)/WetlandStrategy.cpp

# Test executables
TEST_STATE = test_state.exe
TEST_STRATEGY = test_strategy.exe

# Default target
all: $(TEST_STATE) $(TEST_STRATEGY)

# Compile State Pattern tests
$(TEST_STATE): test_state.cpp
	@echo "Compiling State Pattern tests..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) test_state.cpp \
		"$(STATE_DIR)/Plant.cpp" \
		"$(STATE_DIR)/SeedlingState.cpp" \
		"$(STATE_DIR)/GrowingState.cpp" \
		"$(STATE_DIR)/MatureState.cpp" \
		"$(STATE_DIR)/WiltingState.cpp" \
		"$(STATE_DIR)/DeadState.cpp" \
		-o $(TEST_STATE)
	@echo "State tests compiled successfully!"

# Compile Strategy Pattern tests
$(TEST_STRATEGY): test_strategy.cpp
	@echo "Compiling Strategy Pattern tests..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) test_strategy.cpp \
		"$(STRATEGY_DIR)/Plant.cpp" \
		"$(STRATEGY_DIR)/DesertStrategy.cpp" \
		"$(STRATEGY_DIR)/TropicalStrategy.cpp" \
		"$(STRATEGY_DIR)/IndoorStrategy.cpp" \
		"$(STRATEGY_DIR)/MediterraneanStrategy.cpp" \
		"$(STRATEGY_DIR)/WetlandStrategy.cpp" \
		-o $(TEST_STRATEGY)
	@echo "Strategy tests compiled successfully!"

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
	@echo "All tests completed!"

# Clean executables
clean:
	@echo "Cleaning test executables..."
	rm -f $(TEST_STATE) $(TEST_STRATEGY)
	@echo "Clean complete!"

# Run only state tests
test-state: $(TEST_STATE)
	@echo "Running State Pattern Tests..."
	./$(TEST_STATE)

# Run only strategy tests
test-strategy: $(TEST_STRATEGY)
	@echo "Running Strategy Pattern Tests..."
	./$(TEST_STRATEGY)

.PHONY: all run clean test-state test-strategy
