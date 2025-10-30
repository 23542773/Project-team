#ifndef PLANTBEDMEMENTO_H
#define PLANTBEDMEMENTO_H

#include <vector>
#include "Plant.h"

/**
 * @class PlantBedMemento
 * @brief Snapshot of a Bed's plants for safe concurrent iteration
 */
class PlantBedMemento {
private:
    std::vector<Plant*> snapshot;

public:
    PlantBedMemento(const std::vector<Plant*>& plants) : snapshot(plants) {}

    const std::vector<Plant*>& getSnapshot() const { return snapshot; }
};

#endif 
