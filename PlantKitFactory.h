#ifndef PLANTKITFACTORY_H
#define PLANTKITFACTORY_H

#include <string>
#include "Plant.h"
#include "SoilMix.h"
#include "Pot.h"
#include "PlantFlyweight.h"

class PlantKitFactory{

    public:
        virtual ~PlantKitFactory() = default;
        virtual Plant* createPlant(const std::string& id, PlantFlyweight* sf) =0;
        virtual Pot* createPot()=0;
        virtual SoilMix* createSoilMix() = 0;

};

class DesertFactory : public PlantKitFactory{

    public:
    Plant* createPlant(const std::string& id, PlantFlyweight* sf) override;
    Pot* createPot() override;
    SoilMix* createSoilMix() override;
};

class TropicalFactory : public PlantKitFactory {
public:
    Plant* createPlant(const std::string& id, PlantFlyweight* sf) override;
    Pot* createPot() override;
    SoilMix* createSoilMix() override;
};

class IndoorFactory : public PlantKitFactory {
public:
    Plant* createPlant(const std::string& id, PlantFlyweight* sf) override;
    Pot* createPot() override;
    SoilMix* createSoilMix() override;
};

class MediterraneanFactory : public PlantKitFactory {
public:
    Plant* createPlant(const std::string& id, PlantFlyweight* sf) override;
    Pot* createPot() override;
    SoilMix* createSoilMix() override;
};

class WetlandFactory : public PlantKitFactory {
public:
    Plant* createPlant(const std::string& id, PlantFlyweight* sf) override;
    Pot* createPot() override;
    SoilMix* createSoilMix() override;
};

#endif