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

# Decorator Pattern Files
DECORATOR_SOURCES = $(PATTERN_DIR)/PlantItem.cpp \
                    $(PATTERN_DIR)/ReinforcedPot.cpp \
                    $(PATTERN_DIR)/GiftWrap.cpp \
                    $(PATTERN_DIR)/MessageCard.cpp \
                    $(PATTERN_DIR)/Plant.cpp \
                    $(PATTERN_DIR)/SpeciesFlyweight.cpp \
                    $(PATTERN_DIR)/UnsharedSpeciesFlyweight.cpp \
                    $(PATTERN_DIR)/SeedlingState.cpp \
                    $(PATTERN_DIR)/GrowingState.cpp \
                    $(PATTERN_DIR)/MatureState.cpp \
                    $(PATTERN_DIR)/WiltingState.cpp \
                    $(PATTERN_DIR)/DeadState.cpp \
                    $(PATTERN_DIR)/SoilMix.cpp \
                    $(PATTERN_DIR)/SandySoilMix.cpp \
                    $(PATTERN_DIR)/Pot.cpp \
                    $(PATTERN_DIR)/CeramicPot.cpp

# Mediator Pattern Files
MEDIATOR_SOURCES = $(PATTERN_DIR)/ChatMediator.cpp \
                   $(PATTERN_DIR)/Customer.cpp \
                   $(PATTERN_DIR)/Staff.cpp

# Test executables
TEST_STATE = test_state.exe
TEST_STRATEGY = test_strategy.exe
TEST_FLYWEIGHT = test_flyweight.exe
TEST_DECORATOR = test_decorator.exe
TEST_MEDIATOR = test_mediator.exe

# Default target
all: $(TEST_STATE) $(TEST_STRATEGY) $(TEST_FLYWEIGHT) $(TEST_DECORATOR) $(TEST_MEDIATOR)

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

# Compile Decorator Pattern tests
$(TEST_DECORATOR): test_decorator.cpp
	@echo "Compiling Decorator Pattern tests..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) test_decorator.cpp \
		"$(PATTERN_DIR)/PlantItem.cpp" \
		"$(PATTERN_DIR)/ReinforcedPot.cpp" \
		"$(PATTERN_DIR)/GiftWrap.cpp" \
		"$(PATTERN_DIR)/MessageCard.cpp" \
		"$(PATTERN_DIR)/Plant.cpp" \
		"$(PATTERN_DIR)/SpeciesFlyweight.cpp" \
		"$(PATTERN_DIR)/UnsharedSpeciesFlyweight.cpp" \
		"$(PATTERN_DIR)/SeedlingState.cpp" \
		"$(PATTERN_DIR)/GrowingState.cpp" \
		"$(PATTERN_DIR)/MatureState.cpp" \
		"$(PATTERN_DIR)/WiltingState.cpp" \
		"$(PATTERN_DIR)/DeadState.cpp" \
		"$(PATTERN_DIR)/SoilMix.cpp" \
		"$(PATTERN_DIR)/SandySoilMix.cpp" \
		"$(PATTERN_DIR)/Pot.cpp" \
		"$(PATTERN_DIR)/CeramicPot.cpp" \
		-o $(TEST_DECORATOR)
	@echo "Decorator tests compiled successfully!"

# Compile Mediator Pattern tests
$(TEST_MEDIATOR): test_mediator.cpp
	@echo "Compiling Mediator Pattern tests..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) test_mediator.cpp \
		-o $(TEST_MEDIATOR)
	@echo "Mediator tests compiled successfully!"

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
	@echo "=========================================="
	@echo "Running Decorator Pattern Tests..."
	@echo "=========================================="
	./$(TEST_DECORATOR)
	@echo ""
	@echo "=========================================="
	@echo "Running Mediator Pattern Tests..."
	@echo "=========================================="
	./$(TEST_MEDIATOR)
	@echo ""
	@echo "All tests completed!"

# Clean executables
clean:
	@echo "Cleaning test executables..."
	rm -f $(TEST_STATE) $(TEST_STRATEGY) $(TEST_FLYWEIGHT) $(TEST_DECORATOR) $(TEST_MEDIATOR)
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

# Run only decorator tests
test-decorator: $(TEST_DECORATOR)
	@echo "Running Decorator Pattern Tests..."
	./$(TEST_DECORATOR)

# Run only mediator tests
test-mediator: $(TEST_MEDIATOR)
	@echo "Running Mediator Pattern Tests..."
	./$(TEST_MEDIATOR)

.PHONY: all run clean test-state test-strategy test-flyweight test-decorator test-mediator
