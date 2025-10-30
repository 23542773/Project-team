#ifndef FLYWEIGHTSKUITERATOR_H
#define FLYWEIGHTSKUITERATOR_H

#include <vector>
#include <utility>
#include <string>
#include <memory>
#include "PlantFlyweight.h"
#include "SpeciesCatalog.h"
#include <stdexcept>


class FlyweightSKUIterator {
private:
    std::vector<std::pair<std::string, std::shared_ptr<PlantFlyweight>>> entries;
    size_t current;

public:
    explicit FlyweightSKUIterator(const SpeciesCatalog& catalog);
    bool hasNext() const;
    std::pair<std::string, std::shared_ptr<PlantFlyweight>> next();
    void reset();
};

#endif
