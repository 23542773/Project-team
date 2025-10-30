# Unit Testing - Iterator & Flyweight Patterns

This directory contains unit tests for Iterator and Flyweight design patterns using the doctest framework.

## Test Files

- `IteratorTest.cpp` - Unit tests for Iterator Pattern (Bed, Greenhouse, PlantBedIterator, GreenhouseIterator)
- `FlyWeightTest.cpp` - Unit tests for Flyweight Pattern (SpeciesCatalog, SpeciesFlyweight, UnsharedSpeciesFlyweight)

## Running Tests

### Using Make
```bash
cd tests
make runIt      # Run Iterator pattern tests
make runFly     # Run Flyweight pattern tests  
make clean      # Remove compiled executables