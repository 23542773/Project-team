#ifndef POT_H
#define POT_H

#include <string>

class Pot {

private:
    int cost;

public:
    Pot(int c = 0) : cost(c) {}
    virtual ~Pot() = default;
    virtual std::string name() const = 0;
    int getCost() const { return cost; }
};

class TerracottaPot : public Pot {
public:
    TerracottaPot() : Pot(15) {}
    std::string name() const override { return "Terracotta Pot"; }
};

class GlazedCeramicPot : public Pot {
public:
    GlazedCeramicPot() : Pot(25) {}
    std::string name() const override { return "Glazed Ceramic Pot"; }
};

class CeramicPot : public Pot {
public:
    CeramicPot() : Pot(20) {}
    std::string name() const override { return "Ceramic Pot"; }
};

class UnglazedClayPot : public Pot {
public:
    UnglazedClayPot() : Pot(18) {}
    std::string name() const override { return "Unglazed Clay Pot"; }
};

class AquaticBasketPot : public Pot {
public:
    AquaticBasketPot() : Pot(23) {}
    std::string name() const override { return "Aquatic Basket Pot"; }
};

#endif
