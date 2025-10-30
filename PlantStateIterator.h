#ifndef PLANTSTATEITERATOR_H
#define PLANTSTATEITERATOR_H

#include "PlantIterator.h"
#include "Greenhouse.h"
#include "Plant.h"
#include <vector>
#include <stdexcept>
#include <algorithm>


class PlantStateIterator : public PlantIterator<Plant*> {
private:
    std::vector<Plant*> allPlants;
    size_t current;

public:
    explicit PlantStateIterator(const Greenhouse& gh);
        

    bool hasNext() const override;
    Plant*& next() override;
    void reset() override;
    void goTo(size_t index) override;
    size_t currentIndex() const override;
};

#endif
