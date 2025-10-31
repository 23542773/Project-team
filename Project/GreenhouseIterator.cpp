#include "GreenhouseIterator.h"

GreenhouseIterator::GreenhouseIterator(const std::vector<Plant*>& plants): plants(plants), current(0) {}
    
void GreenhouseIterator::first()  
{
    current = 0;
}
    
void GreenhouseIterator::next()  
{
    if (!isDone()) 
    {
        ++current;
    }
}
    
bool GreenhouseIterator::isDone() const  
{
    return current >= plants.size();
}
    
Plant* GreenhouseIterator::currentItem() const  
{
    return isDone() ? nullptr : plants[current];
}