#ifndef WITINGSTATE_H
#define WITINGSTATE_H

#include "PlantState.h"

class WiltingState : public PlantState {

    public:
        void onTick(Plant& p) override;
        void onWater(Plant& p) override;

};

#endif//WITINGSTATE_H