#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include "PlantContainer.h"
#include "PlantIterator.h"
#include "PlantStateIterator.h"
#include "Bed.h"
#include <vector>
#include "Plant.h"
#include "PlantBedIterator.h"

class Bed;


/**
 * @class Greenhouse
 * @brief Concrete container for storing beds in a greenhouse (Iterator Pattern)
 * 
 * Inherits from PlantContainer<Bed*> and contains a vector of Bed pointers.
 * Provides an iterator (GreenhouseIterator) to traverse beds without exposing
 * the internal structure.
 */
class Greenhouse : public PlantContainer<Plant*> {
private:
    std::vector<Bed*> beds;

public:
    /**
     * @brief Constructor
     */
    Greenhouse() = default;
    
    /**
     * @brief Destructor
     */
    ~Greenhouse() override = default;

    /**
     * @brief Create an iterator for this greenhouse
     * @return Pointer to PlantIterator for Bed*
     */
    PlantIterator<Plant*>* createIterator() override;

    /**
     * @brief Get the vector of beds
     * @return Reference to the beds vector
     */
    std::vector<Bed*>& getBeds();
    const std::vector<Bed*>& getBeds() const;

    void addBed(Bed* bed);

    /**
     * @brief Remove a bed from the greenhouse
     * @param bed Pointer to bed to remove
     * @return True if bed was found and removed, false otherwise
     */
    bool removeBed(Bed* bed);

    /**
     * @brief Remove bed by index
     * @param index Index of bed to remove
     * @return True if index was valid, false otherwise
     */
    bool removeBed(size_t index);

    
    size_t size() const;
    bool empty() const;
    void clear();
    Bed* getBed(size_t index) const;

    std::vector<Plant*> getAllPlants() const;
};

#endif // GREENHOUSE_H