#include "PlantBedIterator.h"

PlantBedIterator::PlantBedIterator(Bed& bed) 
    : plants(bed.getPlants()), current(0) {}

bool PlantBedIterator::hasNext() const {
    return current < plants.size();
}

Plant*& PlantBedIterator::next() {
    if (!hasNext()) throw std::out_of_range("No more plants");
    return plants[current++];
}

void PlantBedIterator::reset() {
    current = 0;
}

void PlantBedIterator::goTo(size_t index) {
    if (index >= plants.size()) throw std::out_of_range("Index out of range");
    current = index;
}

size_t PlantBedIterator::currentIndex() const {
    return current;
}
