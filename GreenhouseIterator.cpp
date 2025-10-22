#include "GreenhouseIterator.h"
#include "Greenhouse.h"
#include "Bed.h"

GreenhouseIterator::GreenhouseIterator(Greenhouse& greenhouse) : gh(greenhouse), currentIndex(0) { }

GreenhouseIterator::~GreenhouseIterator() { }

Bed*& GreenhouseIterator::next() {
    return gh.getBeds()[currentIndex++];
}

bool GreenhouseIterator::hasNext() {
    return currentIndex < gh.getBeds().size();
}