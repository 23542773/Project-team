#include "Plant.h"

        Plant::Plant() {

        };

        Plant::~Plant() { delete state; };
    
        void Plant::water() {};
        void Plant::fertilize() {};
        void Plant::tickDay() {};
        void Plant::setState(PlantState* s) {};