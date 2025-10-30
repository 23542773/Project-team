#ifndef PLANTITERATOR_H
#define PLANTITERATOR_H

#include <cstddef> 

/**
 * @class PlantIterator
 * @brief Abstract template iterator interface (Iterator Pattern)
 * 
 * Defines the interface for iterating over collections of type T
 * @tparam T The type of elements to iterate over
 */
template <typename T>
class PlantIterator {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~PlantIterator() {}
    
    /**
     * @brief Get the next element in the collection
     * @return Reference to the next element of type T
     */
    virtual T& next() = 0;
    
    /**
     * @brief Check if there are more elements
     * @return True if there is a next element, false otherwise
     */
    virtual bool hasNext() = 0;

    virtual void goTo(size_t index) = 0;
    virtual void reset() = 0;
    virtual size_t currentIndex() const = 0;
};

#endif // PLANTITERATOR_H