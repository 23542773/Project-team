#ifndef PLANTFLYWEIGHT_H
#define PLANTFLYWEIGHT_H

#include <string>

class PlantFlyweight {
    public:
    
    virtual ~PlantFlyweight() = default;
    virtual std::string speciesName() const = 0;
    virtual std::string envType() const = 0;
    //virtual CarePresets getCareDefaults() const = 0;
    virtual int getCost() const = 0;

};

#endif