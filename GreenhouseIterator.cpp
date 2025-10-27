#include "GreenhouseIterator.h"
#include "Greenhouse.h"
#include "Bed.h"

GreenhouseIterator::GreenhouseIterator(Greenhouse& greenhouse) : gh(greenhouse), Index(0) { }

GreenhouseIterator::~GreenhouseIterator() { }

Bed*& GreenhouseIterator::next() {
    return gh.getBeds()[Index++];
}

bool GreenhouseIterator::hasNext() {
    return Index < gh.getBeds().size();
}

void GreenhouseIterator::goTo(size_t index) {
    if (index < gh.getBeds().size())
        Index = index;
}

void GreenhouseIterator::reset() {
    Index = 0;
}

size_t GreenhouseIterator::currentIndex() const {
    return Index;
}