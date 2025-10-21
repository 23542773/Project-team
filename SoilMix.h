#ifndef SOILMIX_H
#define SOILMIX_H

#include <string>

class SoilMix {

private:
    int cost;

public:
    SoilMix(int c = 0) : cost(c) {}
    virtual ~SoilMix() = default;
    virtual std::string name() const = 0;
    int getCost() const { return cost; }
};

class SandySoilMix : public SoilMix {
public:
    SandySoilMix() : SoilMix(20) {} // Example price
    std::string name() const override { return "Sandy Soil Mix"; }
};

class PeatSoilMix : public SoilMix {
public:
    PeatSoilMix() : SoilMix(25) {}
    std::string name() const override { return "Peat Soil Mix"; }
};

class LightAirySoilMix : public SoilMix {
public:
    LightAirySoilMix() : SoilMix(30) {}
    std::string name() const override { return "Light Airy Soil Mix"; }
};

class GrittyLimeSoilMix : public SoilMix {
public:
    GrittyLimeSoilMix() : SoilMix(22) {}
    std::string name() const override { return "Gritty Lime Soil Mix"; }
};

class AquaticSoilMix : public SoilMix {
public:
    AquaticSoilMix() : SoilMix(28) {}
    std::string name() const override { return "Aquatic Soil Mix"; }
};

#endif
