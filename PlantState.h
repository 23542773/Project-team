#ifndef PLANTSTATE_H
#define PLANTSTATE_H

class Plant;

class PlantState {

    public:


        virtual void onTick(Plant& p) = 0;
        virtual void onWater(Plant& p) = 0;
        virtual bool canSell();
};

#endif//PLANTSTATE_H