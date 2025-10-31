#include "SkuIterator.h"

SkuIterator::SkuIterator(const std::vector<Plant*>& plants, const std::string& sku) : plants(plants), targetSku(sku), current(0)
{
    first();
}
    
void SkuIterator::first() 
{
    current = 0;
    advanceToMatch();
}
    
void SkuIterator::next()  
{
    if (!isDone()) 
    {
        ++current;
        advanceToMatch();
    }
}
    
bool SkuIterator::isDone() const  
{
    return current >= plants.size();
}
    
Plant* SkuIterator::currentItem() const  
{
    return isDone() ? nullptr : plants[current];
}

void SkuIterator::advanceToMatch() 
{
    while (current < plants.size() && (!plants[current] || plants[current]->sku() != targetSku)) 
    {
        ++current;
    }
}