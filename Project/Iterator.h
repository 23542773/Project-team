#ifndef ITERATOR_H
#define ITERATOR_H

class Plant;

/// \brief Abstract Iterator interface for traversing plants

class Iterator 
{
    
public:
    virtual ~Iterator() = default;
    
    /// \brief Move to the first element
    virtual void first() = 0;
    
    /// \brief Move to the next element
    virtual void next() = 0;
    
    /// \brief Check if iteration is complete
    virtual bool isDone() const = 0;
    
    /// \brief Get the current plant (returns nullptr if isDone)
    virtual Plant* currentItem() const = 0;
};

#endif
