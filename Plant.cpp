#include "Plant.h"

Plant::Plant() : state(nullptr) {}

Plant::~Plant() {}

Plant::Plant(const Plant& other) {
    id = other.id;
    colour = other.colour;
    name = other.name;
    biome = other.biome;
    health = other.health;
    ageInDays = other.ageInDays;
    moistureLevel = other.moistureLevel;
    humidity = other.humidity;
    temp = other.temp;
    height = other.height;
    rootDepth = other.rootDepth;
    lightExp = other.lightExp;
    soilPh = other.soilPh;
    costPerDay = other.costPerDay;
    state = other.state;
}

Plant* Plant::clone(std::string plantId, std::string colour) {
    Plant* cloned = new Plant(*this);
    cloned->id = plantId;
    cloned->colour = colour;
    return cloned;
}

void Plant::water() {
    moistureLevel += biome.waterPerDay;
    if (moistureLevel>100) moistureLevel = 100;
}

void Plant::fertilize() {
    health += 5;
    if (health>100) health = 100;
}

void Plant::tickDay() {
    ageInDays += 1;
    moistureLevel -= 5;
    if (moistureLevel<0) moistureLevel = 0;
    if (moistureLevel<20) health -= 2;
    if (health<0) health = 0;
}

void Plant::addWater(int amount) {
    moistureLevel += amount;
    if (moistureLevel>100) moistureLevel = 100;
}

void Plant::addHealth(int amount) {
    health += amount;
    if (health>100) health = 100;
    if (health<0) health = 0;
}

void Plant::setState(PlantState* s) {
    state = s;
}

Biome Plant::getBiome() { return biome; }

int Plant::getHealth() { return health; }

float Plant::getCost() { return costPerDay; }

float Plant::getAgeDays() { return ageInDays; }

float Plant::getMoisture() { return moistureLevel; }

std::string Plant::getID() { return id; }

std::string Plant::getName() { return name; }

std::string Plant::getColour() { return colour; }
