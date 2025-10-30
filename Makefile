# Makefile for Plant Nursery Facade Testing
# Author: Damian Moustakis - COS 214 Project
# Author: Locutus-0201
# Date: 2025-10-30 11:31:27 UTC
# Project: Plant Nursery Simulator - Unified Facade Pattern Implementation

# ============================================================================
#                           COMPILER CONFIGURATION
# ============================================================================

CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g

# ============================================================================
#                           SOURCE FILES
# ============================================================================

# Unified facade source file (single facade now!)
FACADE_SRC = NurseryFacade.cpp

# Dummy implementation files (in root directory)
DUMMY_SRC = DummySpeciesCatalog.cpp \
            DummyInventoryService.cpp \
            DummySalesService.cpp \
            DummyPlantFlyweight.cpp \
            DummyPlant.cpp \
            DummyPlantState.cpp \
            DummyPlantKitFactory.cpp \
            DummyPackageDirector.cpp

# Test files
TEST_SRC = test_facade.cpp
UNIT_TEST_SRC = test_facade_unit.cpp

# All source files
ALL_SRC = $(FACADE_SRC) $(DUMMY_SRC) $(TEST_SRC)

# ============================================================================
#                           OBJECT FILES
# ============================================================================

# Object files (replace .cpp with .o)
FACADE_OBJ = $(FACADE_SRC:.cpp=.o)
DUMMY_OBJ = $(DUMMY_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
ALL_OBJ = $(ALL_SRC:.cpp=.o)

# ============================================================================
#                           OUTPUT TARGETS
# ============================================================================

# Output executables
TARGET = test_facade
UNIT_TEST_TARGET = test_facade_unit

# Google Test flags
GTEST_FLAGS = -lgtest -lgtest_main -pthread

# ============================================================================
#                           DEFAULT TARGET
# ============================================================================

# Default target - build everything
all: $(TARGET)
	@echo "========================================="
	@echo "  Build Complete!"
	@echo "  Run with: ./$(TARGET)"
	@echo "  Or run: make test"
	@echo "========================================="

# ============================================================================
#                        INTEGRATION TEST TARGETS
# ============================================================================

# Link all object files into executable
$(TARGET): $(ALL_OBJ)
	@echo "Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✓ Executable created: $(TARGET)"

# Compile .cpp files to .o files
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run integration tests
test: $(TARGET)
	@echo ""
	@echo "========================================="
	@echo "  Running Integration Tests..."
	@echo "========================================="
	@./$(TARGET)

# Run without rebuilding
run: $(TARGET)
	@./$(TARGET)

# ============================================================================
#                           UNIT TEST TARGETS
# ============================================================================

# Build unit tests
unit: $(FACADE_OBJ) $(DUMMY_OBJ)
	@echo "Building unit tests..."
	$(CXX) $(CXXFLAGS) -o $(UNIT_TEST_TARGET) $(UNIT_TEST_SRC) $(FACADE_OBJ) $(DUMMY_OBJ) $(GTEST_FLAGS)
	@echo "✓ Unit test executable created: $(UNIT_TEST_TARGET)"

# Run unit tests
unit-test: unit
	@echo ""
	@echo "========================================="
	@echo "  Running Unit Tests (Google Test)"
	@echo "========================================="
	@./$(UNIT_TEST_TARGET)

# Run unit tests with verbose output
unit-verbose: unit
	@echo ""
	@echo "========================================="
	@echo "  Running Unit Tests (Verbose Mode)"
	@echo "========================================="
	@./$(UNIT_TEST_TARGET) --gtest_print_time=1 --gtest_color=yes

# Run specific unit test
unit-filter: unit
	@echo "Running filtered tests..."
	@./$(UNIT_TEST_TARGET) --gtest_filter=$(FILTER)

# ============================================================================
#                           UTILITY TARGETS
# ============================================================================

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(ALL_OBJ) $(TARGET) $(UNIT_TEST_TARGET)
	@echo "✓ Clean complete"

# Rebuild everything from scratch
rebuild: clean all

# Rebuild unit tests from scratch
rebuild-unit: clean unit

# Show compilation commands (verbose mode)
verbose: CXXFLAGS += -v
verbose: all

# ============================================================================
#                        VALIDATION TARGETS
# ============================================================================

# Check file structure
check:
	@echo "Checking file structure..."
	@echo ""
	@echo "=== Facade Files ==="
	@ls -1 $(FACADE_SRC) 2>/dev/null || echo "  ✗ Missing facade files"
	@echo ""
	@echo "=== Dummy Files ==="
	@ls -1 $(DUMMY_SRC) 2>/dev/null || echo "  ✗ Missing dummy files"
	@echo ""
	@echo "=== Test Files ==="
	@ls -1 $(TEST_SRC) 2>/dev/null || echo "  ✗ Missing integration test files"
	@ls -1 $(UNIT_TEST_SRC) 2>/dev/null || echo "  ✗ Missing unit test files"
	@echo ""

# Verify Google Test installation
check-gtest:
	@echo "Checking Google Test installation..."
	@which g++ > /dev/null && echo "✓ g++ compiler found" || echo "✗ g++ not found"
	@ldconfig -p | grep libgtest > /dev/null && echo "✓ Google Test libraries found" || echo "✗ Google Test not installed"
	@echo ""
	@echo "To install Google Test, run:"
	@echo "  sudo apt-get update"
	@echo "  sudo apt-get install -y libgtest-dev cmake"
	@echo "  cd /usr/src/gtest && sudo cmake . && sudo make && sudo cp lib/*.a /usr/lib"

# ============================================================================
#                           TESTING TARGETS
# ============================================================================

# Run all tests (integration + unit)
test-all: test unit-test
	@echo ""
	@echo "========================================="
	@echo "  All Tests Complete!"
	@echo "========================================="

# Run tests with coverage (requires gcov)
coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage
coverage: clean test-all
	@echo "Generating coverage report..."
	@gcov $(FACADE_SRC) $(DUMMY_SRC)
	@echo "✓ Coverage files generated (.gcov)"

# ============================================================================
#                           HELP TARGET
# ============================================================================

# Show help
help:
	@echo "========================================="
	@echo "  Makefile Commands"
	@echo "========================================="
	@echo ""
	@echo "BUILD COMMANDS:"
	@echo "  make              - Build integration tests"
	@echo "  make unit         - Build unit tests"
	@echo "  make all          - Build all targets"
	@echo ""
	@echo "TEST COMMANDS:"
	@echo "  make test         - Run integration tests"
	@echo "  make unit-test    - Run unit tests"
	@echo "  make test-all     - Run all tests"
	@echo "  make unit-verbose - Run unit tests (verbose)"
	@echo "  make run          - Run integration tests (no rebuild)"
	@echo ""
	@echo "UTILITY COMMANDS:"
	@echo "  make clean        - Remove build artifacts"
	@echo "  make rebuild      - Clean and rebuild all"
	@echo "  make rebuild-unit - Clean and rebuild unit tests"
	@echo "  make check        - Verify file structure"
	@echo "  make check-gtest  - Verify Google Test installation"
	@echo ""
	@echo "ADVANCED COMMANDS:"
	@echo "  make verbose      - Build with verbose output"
	@echo "  make coverage     - Generate code coverage report"
	@echo "  make unit-filter FILTER='*TestName*' - Run specific tests"
	@echo ""
	@echo "EXAMPLES:"
	@echo "  make test                              - Run integration tests"
	@echo "  make unit-test                         - Run unit tests"
	@echo "  make unit-filter FILTER='*Restock*'    - Run restock tests only"
	@echo "========================================="

# ============================================================================
#                        PHONY TARGETS
# ============================================================================

# Declare phony targets (targets that don't create files)
.PHONY: all clean test run rebuild verbose check help \
        unit unit-test unit-verbose unit-filter test-all \
        coverage check-gtest rebuild-unit

# ============================================================================
#                        DEPENDENCY TRACKING
# ============================================================================

# Recompile if header files change
NurseryFacade.o: NurseryFacade.cpp NurseryFacade.h \
                 SpeciesCatalog.h InventoryService.h SalesService.h \
                 PlantKitFactory.h PackageDirector.h CustomPlantPackage.h OrderItem.h

DummySpeciesCatalog.o: DummySpeciesCatalog.cpp DummySpeciesCatalog.h \
                       DummyPlantFlyweight.h

DummyInventoryService.o: DummyInventoryService.cpp DummyInventoryService.h \
                         DummyPlant.h

DummySalesService.o: DummySalesService.cpp DummySalesService.h \
                     DummyOrderItem.h

DummyPlantFlyweight.o: DummyPlantFlyweight.cpp DummyPlantFlyweight.h

DummyPlant.o: DummyPlant.cpp DummyPlant.h \
              DummyPlantFlyweight.h DummyPlantState.h

DummyPlantState.o: DummyPlantState.cpp DummyPlantState.h DummyPlant.h

DummyPlantKitFactory.o: DummyPlantKitFactory.cpp DummyPlantKitFactory.h \
                        DummyPlant.h DummyPlantFlyweight.h

DummyPackageDirector.o: DummyPackageDirector.cpp DummyPackageDirector.h

test_facade.o: test_facade.cpp NurseryFacade.h \
               DummySpeciesCatalog.h DummyInventoryService.h DummySalesService.h \
               DummyPlantKitFactory.h DummyPackageDirector.h DummyOrderItem.h \
               DummyPlant.h DummyPlantState.h DummyPlantFlyweight.h

# ============================================================================
#                           END OF MAKEFILE
# ============================================================================