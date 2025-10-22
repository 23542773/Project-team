#include "PlantBedIterator.h"
#include "Bed.h"
#include "Plant.h"

PlantBedIterator::PlantBedIterator(Bed& b) : bed(b), currentIndex(0) { }

PlantBedIterator::~PlantBedIterator() { }

Plant*& PlantBedIterator::next() {
    return bed.getPlants()[currentIndex++];
}

bool PlantBedIterator::hasNext() {
    return currentIndex < bed.getPlants().size();
}