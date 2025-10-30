# Unit Testing with doctest

This directory contains unit tests for the State and Strategy design patterns using the doctest framework.

## Test Files

- `test_state.cpp` - Unit tests for State Pattern (SeedlingState, GrowingState, MatureState, WiltingState, DeadState)
- `test_strategy.cpp` - Unit tests for Strategy Pattern (DesertStrategy, TropicalStrategy, IndoorStrategy, MediterraneanStrategy, WetlandStrategy)
- `doctest.h` - Single-header doctest testing framework

## Running Tests


### Option1 : Using Make (if make is installed)

**First, install make on WSL/Linux:**
```bash
sudo apt-get update
sudo apt-get install build-essential
```

**Then run:**
```bash
cd tests
make run
```

Or compile and run individually:
```bash
make test-state     # Run only State pattern tests
make test-strategy  # Run only Strategy pattern tests
make clean          # Remove compiled executables
```



### Option 2: Manual Compilation

**Compile State Pattern Tests:**
```bash
g++ -std=c++11 -I"../Prototype" -I"../Flyweight" -I"../Strategy" -I"../State (with Singleton)" test_state.cpp "../State (with Singleton)/Plant.cpp" "../State (with Singleton)/SeedlingState.cpp" "../State (with Singleton)/GrowingState.cpp" "../State (with Singleton)/MatureState.cpp" "../State (with Singleton)/WiltingState.cpp" "../State (with Singleton)/DeadState.cpp" -o test_state
```

**Run:**
```bash
./test_state
```

**Compile Strategy Pattern Tests:**
```bash
g++ -std=c++11 -I"../Prototype" -I"../Flyweight" -I"../Strategy" -I"../State (with Singleton)" test_strategy.cpp "../Strategy/Plant.cpp" "../Strategy/DesertStrategy.cpp" "../Strategy/TropicalStrategy.cpp" "../Strategy/IndoorStrategy.cpp" "../Strategy/MediterraneanStrategy.cpp" "../Strategy/WetlandStrategy.cpp" -o test_strategy
```

**Run:**
```bash
./test_strategy
```

## Test Coverage

### State Pattern Tests
- ✅ Singleton instance verification for all states
- ✅ State name correctness
- ✅ Maturity checks (only MatureState returns true)
- ✅ State transitions (Seedling → Growing after 5 days)
- ✅ State-specific behaviors (health increases in Seedling)
- ✅ Context delegation (Plant delegates to PlantState)
- ✅ Null state handling

### Strategy Pattern Tests
- ✅ DesertStrategy conditional watering/fertilizing
- ✅ TropicalStrategy, IndoorStrategy, MediterraneanStrategy, WetlandStrategy behaviors
- ✅ Strategy switching at runtime
- ✅ Context delegation (Plant delegates to CareStrategy)
- ✅ Water/fertilize effects and bounds checking (0-100)
- ✅ Multiple plants with different strategies
- ✅ Null strategy handling

## Understanding doctest Output

When you run the tests, you'll see:

```
[doctest] doctest version is "2.4.11"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:  X | X passed | X failed | X skipped
[doctest] assertions: XX | XX passed | X failed |
[doctest] Status: SUCCESS!
```

### Passing Tests
```
✓ All checks passed
```

### Failing Tests
```
test_state.cpp:42: ERROR: CHECK( plant.getHealth() == 105 ) is NOT correct!
  values: CHECK( 100 == 105 )
```

## doctest Commands

Run with different options:

```bash
# Run specific test case
./test_state.exe --test-case="State Pattern - Singleton Instances"

# List all test cases
./test_state.exe --list-test-cases

# Run with verbose output
./test_state.exe --success

# Show duration of tests
./test_state.exe --duration=true
```

## Troubleshooting

### "g++ is not recognized"
- Install MinGW or use Visual Studio's Developer Command Prompt
- Or use online C++ compilers

### Compilation errors about missing files
- Ensure you're running commands from the `tests` directory
- Check that all source files exist in the State and Strategy directories

### Tests fail
- Check that the implementation matches expected behavior
- Review test assertions in the .cpp files
- Some tests may need adjustment based on actual implementation

## Adding New Tests

To add new tests, use this template:

```cpp
TEST_CASE("Description of test suite") {

    SUBCASE("Description of specific test") {
        // Arrange
        Plant plant("id", "color", nullptr, nullptr, nullptr, nullptr, nullptr);

        // Act
        plant.tickDay();

        // Assert
        CHECK(plant.getAgeDays() == 1);
    }
}
```

## References

- doctest documentation: https://github.com/doctest/doctest
- doctest tutorial: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
