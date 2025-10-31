#ifndef SKU_ITERATOR_H
#define SKU_ITERATOR_H

#include "Iterator.h"
#include "Plant.h"
#include <vector>
#include <string>

class SkuIterator : public Iterator 
{
public:

    SkuIterator(const std::vector<Plant*>& plants, const std::string& sku);
    
    void first() override;
    
    void next() override;
    
    bool isDone() const override;
    
    Plant* currentItem() const override;

private:

    void advanceToMatch();

    std::vector<Plant*> plants;
    std::string targetSku;
    size_t current;
};

#endif
