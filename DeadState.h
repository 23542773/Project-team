#ifndef DEADSTATE_H
#define DEADSTATE_H

#include "PlantState.h"

class DeadState : public PlantState {

    public:
        void onTick(Plant& p) override;
        void onWater(Plant& p) override;

};

#endif//DEADSTATE_H