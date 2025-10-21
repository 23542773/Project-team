#include "PlantKitFactory.h"

Plant* IndoorFactory::createPlant(const std::string& id, PlantFlyweight* sf) {
    return new Plant(id, sf,createPot(), createSoilMix());
}

Pot* IndoorFactory::createPot() {
    return new CeramicPot();
}

SoilMix* IndoorFactory::createSoilMix() {
    return new LightAirySoilMix();
}
