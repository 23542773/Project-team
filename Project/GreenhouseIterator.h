#ifndef GREENHOUSE_ITERATOR_H
#define GREENHOUSE_ITERATOR_H

#include "Iterator.h"
#include "Plant.h"
#include <vector>

/// \brief Concrete iterator that traverses all plants in the greenhouse
class GreenhouseIterator : public Iterator 
{
public:

    explicit GreenhouseIterator(const std::vector<Plant*>& plants);
    
    void first() override;
    
    void next() override;
    
    bool isDone() const override;
    
    Plant* currentItem() const override;

private:

    std::vector<Plant*> plants;
    size_t current;
};

#endif
