#include "PlantKitFactory.h"

Plant* WetlandFactory::createPlant(const std::string& id, PlantFlyweight* sf) {
    return new Plant(id, sf,createPot(), createSoilMix());
}

Pot* WetlandFactory::createPot() {
    return new AquaticBasketPot();
}

SoilMix* WetlandFactory::createSoilMix() {
    return new AquaticSoilMix();
}
