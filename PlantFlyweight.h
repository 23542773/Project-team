#ifndef PLANT_FLYWEIGHT_H
#define PLANT_FLYWEIGHT_H

#include <string>


/**
 * @class PlantFlyweight
 * @brief Abstract flyweight interface for shared plant data (Flyweight Pattern)
 */
class PlantFlyweight 
{

public:

    virtual ~PlantFlyweight() = default;
    virtual std::string getSku() const = 0;  
    virtual std::string getName() const = 0;
    virtual std::string getBiome() const = 0;
    virtual int getCost()  = 0;
};

#endif