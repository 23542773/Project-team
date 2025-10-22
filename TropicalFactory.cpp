#include "PlantKitFactory.h"

Plant* TropicalFactory::createPlant(const std::string& id, PlantFlyweight* sf) {
    return new Plant(id, sf,createPot(), createSoilMix());
}

Pot* TropicalFactory::createPot() {
    return new GlazedCeramicPot();
}

SoilMix* TropicalFactory::createSoilMix() {
    return new PeatSoilMix();
}
