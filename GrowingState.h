#ifndef GROWINGSTATE_H
#define GROWINGSTATE_H

#include "PlantState.h"

class GrowingState : public PlantState {

    public:
        void onTick(Plant& p) override;
        void onWater(Plant& p) override;

};

#endif//GROWINGSTATE_H