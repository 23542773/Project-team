#include "GreenhouseIterator.h"
#include "Greenhouse.h"
#include "Bed.h"
#include <stdexcept>

GreenhouseIterator::GreenhouseIterator(Greenhouse& greenhouse) : gh(greenhouse), Index(0) { }

Bed*& GreenhouseIterator::next() { return gh.getBeds()[Index++]; }

bool GreenhouseIterator::hasNext() { return Index < gh.getBeds().size(); }

void GreenhouseIterator::goTo(size_t index) { 

    if (index<gh.getBeds().size()) Index = index;
    else throw std::out_of_range("Invalid bed index");
}

void GreenhouseIterator::reset() { Index = 0; }

size_t GreenhouseIterator::currentIndex() const { return Index; }