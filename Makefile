# Makefile for Plant Nursery Facade Testing
# Author: Damian Moustakis - COS 214 Project
# Author: Locutus-0201
# Date: 2025-10-27 22:14:05 UTC
# Project: Plant Nursery Simulator - Facade Pattern Implementation

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Facade source files
FACADE_SRC = NurseryFacade.cpp \
             CustomerNurseryFacade.cpp \
             StaffNurseryFacade.cpp

# Dummy implementation files (in root directory)
DUMMY_SRC = DummySpeciesCatalog.cpp \
            DummyInventoryService.cpp \
            DummySalesService.cpp \
            DummyPlantFlyweight.cpp \
            DummyPlant.cpp \
            DummyPlantState.cpp \
            DummyPlantKitFactory.cpp \
            DummyPackageDirector.cpp

# Test file
TEST_SRC = test_facade.cpp

# All source files
ALL_SRC = $(FACADE_SRC) $(DUMMY_SRC) $(TEST_SRC)

# Object files (replace .cpp with .o)
FACADE_OBJ = $(FACADE_SRC:.cpp=.o)
DUMMY_OBJ = $(DUMMY_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
ALL_OBJ = $(ALL_SRC:.cpp=.o)

# Output executable
TARGET = test_facade

# Default target - build everything
all: $(TARGET)
	@echo "========================================="
	@echo "  Build Complete!"
	@echo "  Run with: ./$(TARGET)"
	@echo "========================================="

# Link all object files into executable
$(TARGET): $(ALL_OBJ)
	@echo "Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✓ Executable created: $(TARGET)"

# Compile .cpp files to .o files
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(ALL_OBJ) $(TARGET)
	@echo "✓ Clean complete"

# Build and run tests
test: $(TARGET)
	@echo ""
	@echo "========================================="
	@echo "  Running Tests..."
	@echo "========================================="
	@./$(TARGET)

# Run without rebuilding
run: $(TARGET)
	@./$(TARGET)

# Rebuild everything from scratch
rebuild: clean all

# Show compilation commands (verbose mode)
verbose: CXXFLAGS += -v
verbose: all

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
	@ls -1 $(TEST_SRC) 2>/dev/null || echo "  ✗ Missing test files"
	@echo ""

# Show help
help:
	@echo "========================================="
	@echo "  Makefile Commands"
	@echo "========================================="
	@echo "  make          - Build the project"
	@echo "  make test     - Build and run tests"
	@echo "  make run      - Run tests (without rebuilding)"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make check    - Verify file structure"
	@echo "  make help     - Show this help message"
	@echo "========================================="

# Declare phony targets (targets that don't create files)
.PHONY: all clean test run rebuild verbose check help

# Dependency tracking (optional but good practice)
# Recompile if header files change
NurseryFacade.o: NurseryFacade.cpp NurseryFacade.h
CustomerNurseryFacade.o: CustomerNurseryFacade.cpp CustomerNurseryFacade.h NurseryFacade.h
StaffNurseryFacade.o: StaffNurseryFacade.cpp StaffNurseryFacade.h NurseryFacade.h
DummySpeciesCatalog.o: DummySpeciesCatalog.cpp DummySpeciesCatalog.h SpeciesCatalog.h
DummyInventoryService.o: DummyInventoryService.cpp DummyInventoryService.h InventoryService.h
DummySalesService.o: DummySalesService.cpp DummySalesService.h SalesService.h
DummyPlantFlyweight.o: DummyPlantFlyweight.cpp DummyPlantFlyweight.h
DummyPlant.o: DummyPlant.cpp DummyPlant.h
DummyPlantState.o: DummyPlantState.cpp DummyPlantState.h
DummyPlantKitFactory.o: DummyPlantKitFactory.cpp DummyPlantKitFactory.h PlantKitFactory.h
DummyPackageDirector.o: DummyPackageDirector.cpp DummyPackageDirector.h PackageDirector.h
test_facade.o: test_facade.cpp CustomerNurseryFacade.h StaffNurseryFacade.h