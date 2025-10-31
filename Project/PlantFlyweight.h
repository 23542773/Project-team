#ifndef PLANT_FLYWEIGHT_H
#define PLANT_FLYWEIGHT_H
#include <string>
enum class Season { Spring, Summer, Autumn, Winter };
class PlantFlyweight 
{

public:

    virtual ~PlantFlyweight() {};
    virtual std::string getSku() = 0;  
    virtual std::string getName()  = 0;
    virtual std::string getBiome() = 0;
    virtual int getCost()  = 0;
    virtual double getWaterSensitivity()  = 0;
    virtual double getInsecticideTolerance()  = 0;
    virtual double getGrowthRate()  = 0;
    virtual Season getThrivingSeason() = 0;
};

#endif