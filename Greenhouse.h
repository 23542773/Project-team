#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include "PlantContainer.h"
#include "PlantIterator.h"
#include <vector>

class Bed;
class GreenhouseIterator;

/**
 * @class Greenhouse
 * @brief Concrete container for storing beds in a greenhouse (Iterator Pattern)
 * 
 * Inherits from PlantContainer<Bed*> and contains a vector of Bed pointers.
 * Provides an iterator (GreenhouseIterator) to traverse beds without exposing
 * the internal structure.
 */
class Greenhouse : public PlantContainer<Bed*> {
private:
    std::vector<Bed*> beds;

public:
    /**
     * @brief Constructor
     */
    Greenhouse();
    
    /**
     * @brief Destructor
     */
    ~Greenhouse();

    /**
     * @brief Create an iterator for this greenhouse
     * @return Pointer to PlantIterator for Bed*
     */
    PlantIterator<Bed*>* createIterator() override;

    /**
     * @brief Get the vector of beds
     * @return Reference to the beds vector
     */
    std::vector<Bed*>& getBeds();
    
    /**
     * @brief Get the vector of beds (const version)
     * @return Const reference to the beds vector
     */
    const std::vector<Bed*>& getBeds() const;
    
    // Friend class for iterator access
    friend class GreenhouseIterator;
};

#endif // GREENHOUSE_H




















