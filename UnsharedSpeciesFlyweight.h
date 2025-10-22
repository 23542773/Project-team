#ifndef UNSHAREDSPECIESFLYWEIGHT_H
#define UNSHAREDSPECIESFLYWEIGHT_H

#include "PlantFlyweight.h"

class UnsharedSpeciesFlyweight : public PlantFlyweight {
private:
    std::string name;
    std::string env;
    //CarePresets cc;
    int cost; // each unshared one can have a unique cost
public:
    UnsharedSpeciesFlyweight(const std::string& name, const std::string& env, /*const CarePresets& cc,*/ int cost)
        : name(name), env(env),/* cc(cc),*/ cost(cost) {}

    std::string speciesName() const override { return name; }
    std::string envType() const override { return env; }
    //CarePresets getCareDefaults() const override { return cc; }

    int getCost() const override { return cost; }
};

#endif
