#include "PlantKitFactory.h"

Plant* MediterraneanFactory::createPlant(const std::string& id, PlantFlyweight* sf) {
    return new Plant(id, sf,createPot(), createSoilMix());
}

Pot* MediterraneanFactory::createPot() {
    return new UnglazedClayPot();
}

SoilMix* MediterraneanFactory::createSoilMix() {
    return new GrittyLimeSoilMix();
}
