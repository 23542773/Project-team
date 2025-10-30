#include "FlyweightSKUIterator.h"
#include <stdexcept>


FlyweightSKUIterator::FlyweightSKUIterator(const SpeciesCatalog& catalog)
    : current(0)
{
    // copy all pairs from the catalog
    for (const auto& entry : catalog.bySku) {
        entries.push_back(entry);
    }
}

bool FlyweightSKUIterator::hasNext() const {
    return current < entries.size();
}

std::pair<std::string, std::shared_ptr<PlantFlyweight>> FlyweightSKUIterator::next() {
    if (!hasNext()) throw std::out_of_range("No more SKUs in catalog");
    return entries[current++];
}

void FlyweightSKUIterator::reset() {
    current = 0;
}
