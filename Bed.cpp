#include "Bed.h"
#include "PlantIterator.h"

Bed::Bed() { }

Bed::~Bed() { }

void Bed::addPlant(Plant* p) {
    plants.push_back(p);
}

bool Bed::removePlant(Plant* p) {
    for (auto it = plants.begin(); it != plants.end(); ++it) {
        if (*it == p) {
            plants.erase(it);
            return true;
        }
    }
    return false;
}

bool Bed::removePlant(size_t index) {
    if (index < plants.size()) {
        plants.erase(plants.begin() + index);
        return true;
    }
    return false;
}

PlantIterator<Plant*>* Bed::createIterator() {
    return nullptr;
}

std::vector<Plant*>& Bed::getPlants() {
    return plants;
}

const std::vector<Plant*>& Bed::getPlants() const {
    return plants;
}