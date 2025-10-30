#ifndef BED_H
#define BED_H

#include "PlantContainer.h"
#include "PlantIterator.h"
#include "PlantStateIterator.h"
#include <vector>
#include "PlantBedMemento.h"
#include "Plant.h"

class Plant;
class PlantBedIterator;

/**
 * @class Bed
 * @brief Concrete container for storing plants in a bed (Iterator Pattern)
 * 
 * Inherits from PlantContainer<Plant*> and contains a vector of Plant pointers.
 * Provides an iterator (PlantBedIterator) to traverse plants without exposing
 * the internal vector structure.
 */
class Bed : public PlantContainer<Plant*> {
private:
    std::vector<Plant*> plants;

public:
    /**
     * @brief Constructor
     */
    Bed();
    
    /**
     * @brief Destructor
     */
    ~Bed();

    void addPlant(Plant* p);
    bool removePlant(Plant* p);
    bool removePlant(size_t index);

    /**
     * @brief Create an iterator for this bed
     * @return Pointer to PlantIterator for Plant*
     */
    PlantIterator<Plant*>* createIterator() override;

    /**
     * @brief Get the vector of plants
     * @return Reference to the plants vector
     */
    std::vector<Plant*>& getPlants();
    
    /**
     * @brief Get the vector of plants (const version)
     * @return Const reference to the plants vector
     */
    const std::vector<Plant*>& getPlants() const;
    
    // Friend class for iterator access
    friend class PlantBedIterator;

     PlantBedMemento* createMemento() const {
        return new PlantBedMemento(plants);
    }

    void restoreFromMemento(PlantBedMemento* m) {
        plants = m->getSnapshot();
    }
};

#endif // BED_H




















