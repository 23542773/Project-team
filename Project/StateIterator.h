#ifndef STATE_ITERATOR_H
#define STATE_ITERATOR_H

#include "Iterator.h"
#include "Plant.h"
#include "PlantState.h"
#include <vector>

class StateIterator : public Iterator 
{
public:

    StateIterator(const std::vector<Plant*>& plants, const PlantState* state);
    
    void first() override;
    
    void next() override;
    
    bool isDone() const override;
    
    Plant* currentItem() const override;

private:

    void advanceToMatch();

    std::vector<Plant*> plants;
    const PlantState* targetState;
    size_t current;
};

#endif
