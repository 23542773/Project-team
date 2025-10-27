#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include "PlantContainer.h"
#include "GreenhouseIterator.h"
#include "Bed.h"
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
    Greenhouse() = default;
    
    /**
     * @brief Destructor
     */
    ~Greenhouse() override = default;

    /**
     * @brief Create an iterator for this greenhouse
     * @return Pointer to PlantIterator for Bed*
     */
    PlantIterator<Bed*>* createIterator() override{

        return new GreenhouseIterator(*this);
    };

    /**
     * @brief Get the vector of beds
     * @return Reference to the beds vector
     */
    std::vector<Bed*>& getBeds(){
        return beds;
    };

    const std::vector<Bed*>& getBeds() const{
        return beds;
    }


    void addBed(Bed* bed){
        beds.push_back(bed);
    };
    
};

#endif // GREENHOUSE_H




















