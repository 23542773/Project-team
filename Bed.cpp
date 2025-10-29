#include "Bed.h"
#include "PlantBedIterator.h"
#include "Plant.h"

Bed::Bed() { }

Bed::~Bed() { }

PlantIterator<Plant*>* Bed::createIterator() {
    return new PlantBedIterator(*this);
}

std::vector<Plant*>& Bed::getPlants() {
    return plants;
}

const std::vector<Plant*>& Bed::getPlants() const {
    return plants;
}