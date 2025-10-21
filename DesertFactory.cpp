#include "PlantKitFactory.h"
#include "Plant.h"
#include "Pot.h"
#include "SoilMix.h"

Plant* DesertFactory::createPlant(const std::string& id, PlantFlyweight* sf) {
    return new Plant(id, sf,createPot(), createSoilMix());
}

Pot* DesertFactory::createPot() {
    return new TerracottaPot();
}

SoilMix* DesertFactory::createSoilMix() {
    return new SandySoilMix();
}
