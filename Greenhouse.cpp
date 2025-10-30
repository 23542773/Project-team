#include "Greenhouse.h"

PlantIterator<Plant*>* Greenhouse::createIterator() {
    return new PlantStateIterator(*this);
}

std::vector<Bed*>& Greenhouse::getBeds() { return beds; }

const std::vector<Bed*>& Greenhouse::getBeds() const { return beds; }

void Greenhouse::addBed(Bed* bed) { beds.push_back(bed); }

bool Greenhouse::removeBed(Bed* bed) {

    for (auto it=beds.begin(); it!=beds.end(); ++it) {

        if (*it==bed) {

            beds.erase(it);
            return true;
        }//END_if
    }//END_it

    return false;
}

bool Greenhouse::removeBed(size_t index) {

    if (index<beds.size()) {

        beds.erase(beds.begin()+index);
        return true;
    }

    return false;
}

size_t Greenhouse::size() const { return beds.size(); }

bool Greenhouse::empty() const { return beds.empty(); }

void Greenhouse::clear() { beds.clear(); }

Bed* Greenhouse::getBed(size_t index) const { return (index<beds.size())? beds[index] : nullptr; }

std::vector<Plant*> Greenhouse::getAllPlants() const {
    std::vector<Plant*> all;
    for (auto* bed : beds) {
        for (auto* p : bed->getPlants()) {
            all.push_back(p);
        }
    }
    return all;
}