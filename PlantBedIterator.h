#ifndef PLANTBEDITERATOR_H
#define PLANTBEDITERATOR_H

#include "PlantIterator.h"
#include "Bed.h"
#include "Plant.h"
#include <vector>
#include <stdexcept>

class Bed;

class PlantBedIterator : public PlantIterator<Plant*> {
private:
    std::vector<Plant*>& plants;
    size_t current;

public:
    explicit PlantBedIterator(Bed& bed);

    bool hasNext() const override;
    Plant*& next() override;
    void reset() override;
    void goTo(size_t index) override;
    size_t currentIndex() const override;
};

#endif
