#ifndef PLANTCONTAINER_H
#define PLANTCONTAINER_H

// Forward declaration
template <typename T>
class PlantIterator;

/**
 * @class PlantContainer
 * @brief Abstract template container interface (Iterator Pattern)
 * 
 * Defines the interface for containers that can create iterators
 * @tparam T The type of elements the container holds
 */
template <typename T>
class PlantContainer {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~PlantContainer() {}
    
    /**
     * @brief Create an iterator for this container
     * @return Pointer to a PlantIterator for type T
     */
    virtual PlantIterator<T>* createIterator() = 0;
};

#endif // PLANTCONTAINER_H