#include "StateIterator.h"

StateIterator::StateIterator(const std::vector<Plant*>& plants, const PlantState* state): plants(plants), targetState(state), current(0) 
{
    first(); 
}
    
void StateIterator::first()  
{
        
    current = 0;    
    advanceToMatch();
}
    
void StateIterator::next()  
{
    if (!isDone()) 
    {
        ++current;
        advanceToMatch();
    }
}
    
bool StateIterator::isDone() const  
{
    return current >= plants.size();
}
    
Plant* StateIterator::currentItem() const  
{
    return isDone() ? nullptr : plants[current];
}

void StateIterator::advanceToMatch() 
{
    while (current < plants.size() && (!plants[current] || plants[current]->getPlantState() != targetState)) 
    {
         ++current;
    }
}