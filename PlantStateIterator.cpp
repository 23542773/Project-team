#include "PlantStateIterator.h"

PlantStateIterator::PlantStateIterator(const Greenhouse& gh) : current(0) {
    // Flatten all plants from all beds
    for (auto* bed : gh.getBeds()) {
        for (auto* plant : bed->getPlants()) {
            allPlants.push_back(plant);
        }
    }
}

bool PlantStateIterator::hasNext() const {
    return current < allPlants.size();
}

Plant*& PlantStateIterator::next() {
    if (!hasNext()) throw std::out_of_range("No more plants");
    return allPlants[current++];
}

void PlantStateIterator::reset() {
    current = 0;
}

void PlantStateIterator::goTo(size_t index) {
    if (index >= allPlants.size()) throw std::out_of_range("Index out of range");
    current = index;
}

size_t PlantStateIterator::currentIndex() const {
    return current;
}
