#include "PlantKitFactory.h"

Plant* PlantKitFactory::createPlant(std::string id, std::string colour, PlantFlyweight* sf)
{
    Pot* pot = createPot();
    SoilMix* soil = createSoilMix();
    CareStrategy* care = careStrategy();
    PlantState* state = &SeedlingState::getInstance();
    return new Plant(id, colour, sf, care, state, soil, pot);
}