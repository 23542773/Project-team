/**
 * @file Iterator.h
 * @brief Defines the abstract Iterator interface, part of the Iterator design pattern.
 */
#ifndef ITERATOR_H
#define ITERATOR_H

// Forward declaration of the item type being iterated over
class Plant;

/**
 * @class Iterator
 * @brief Abstract interface that declares the operations required for traversing a collection of Plant objects.
 *
 * This interface provides a uniform way to access elements of an aggregate object
 * sequentially without exposing its underlying representation.
 */

class Iterator 
{
    
public:
/**
 * @brief Virtual destructor to ensure proper cleanup of derived iterator classes.
 */
    virtual ~Iterator() = default;
    
    /**
     * @brief Resets the iterator's position to the very first element in the collection.
     * This is a pure virtual function and must be implemented by concrete iterators.
     */
    virtual void first() = 0;
    
    /**
     * @brief Moves the iterator to the next element in the collection.
     * This is a pure virtual function and must be implemented by concrete iterators.
     */
    virtual void next() = 0;
    
    /**
     * @brief Checks if the iterator has completed its traversal (i.e., moved past the last element).
     * This is a pure virtual function and must be implemented by concrete iterators.
     * @return true if there are no more elements, false otherwise.
     */
    virtual bool isDone() const = 0;
    
    /**
     * @brief Retrieves the element (Plant pointer) at the current position of the iterator.
     * This is a pure virtual function and must be implemented by concrete iterators.
     * @return A pointer to the current Plant object, or nullptr if `isDone()` is true.
     */
    virtual Plant* currentItem() const = 0;
};

#endif
