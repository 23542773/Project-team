#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"

class MatureState : public PlantState {

    public:
        void onTick(Plant& p) override;
        void onWater(Plant& p) override;
        bool canSell() override;

};

#endif//MATURESTATE_H