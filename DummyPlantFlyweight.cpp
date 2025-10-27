#include "DummyPlantFlyweight.h"

DummyPlantFlyweight::DummyPlantFlyweight(const std::string& type) {
    // TODO: Hardcoded data for known types
    if (type == "aloe") {
        speciesName_ = "Aloe Vera";
        environment_ = "Indoor";
        carePresets_.baseWaterInMl = 250;
        carePresets_.idealLightInHours = 8;
        carePresets_.fertilizeFreqInDays = 30;
    }
    else if (type == "cactus") {
        speciesName_ = "Desert Rose";
        environment_ = "Desert";
        carePresets_.baseWaterInMl = 50;
        carePresets_.idealLightInHours = 12;
        carePresets_.fertilizeFreqInDays = 60;
    }
    else if (type == "orchid") {
        speciesName_ = "Orchid";
        environment_ = "Tropical";
        carePresets_.baseWaterInMl = 400;
        carePresets_.idealLightInHours = 10;
        carePresets_.fertilizeFreqInDays = 21;
    }
    else if (type == "lavender") {
        speciesName_ = "Lavender";
        environment_ = "Mediterranean";
        carePresets_.baseWaterInMl = 200;
        carePresets_.idealLightInHours = 10;
        carePresets_.fertilizeFreqInDays = 45;
    }
    else if (type == "fern") {
        speciesName_ = "Boston Fern";
        environment_ = "Wetland";
        carePresets_.baseWaterInMl = 500;
        carePresets_.idealLightInHours = 6;
        carePresets_.fertilizeFreqInDays = 14;
    }
    else {
        // Defaults
        speciesName_ = "Unknown Plant";
        environment_ = "Unknown";
        carePresets_.baseWaterInMl = 0;
        carePresets_.idealLightInHours = 0;
        carePresets_.fertilizeFreqInDays = 0;
    }
}

std::string DummyPlantFlyweight::speciesName() const {
    return speciesName_;
}

std::string DummyPlantFlyweight::envType() const {
    return environment_;
}

DummyCarePresets DummyPlantFlyweight::careDefaults() const {
    return carePresets_;
}