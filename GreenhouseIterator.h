#ifndef GREENHOUSEITERATOR_H
#define GREENHOUSEITERATOR_H

#include "PlantIterator.h"
#include <cstddef>

class Greenhouse;
class Bed;

/**
 * @class GreenhouseIterator
 * @brief Concrete iterator for Greenhouse that iterates over Bed* objects
 * 
 * Inherits from PlantIterator<Bed*> and implements iteration over beds in a Greenhouse.
 */
class GreenhouseIterator : public PlantIterator<Bed*> {
private:
    Greenhouse& gh;
    size_t currentIndex;

public:
    /**
     * @brief Constructor
     * @param greenhouse Reference to Greenhouse to iterate
     */
    GreenhouseIterator(Greenhouse& greenhouse);
    
    /**
     * @brief Destructor
     */
    ~GreenhouseIterator();
    
    /**
     * @brief Get next bed
     * @return Reference to pointer to next Bed
     */
    Bed*& next() override;

    /**
     * @brief Check if there are more beds
     * @return True if has next, false otherwise
     */
    bool hasNext() override;
};

#endif // GREENHOUSEITERATOR_H




















