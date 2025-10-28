#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"

class SeedlingState : public PlantState {

    public:
        void onTick(Plant& p) override;
        void onWater(Plant& p) override;

};

#endif//SEEDLINGSTATE_H