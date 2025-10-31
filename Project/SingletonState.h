/**
 * @file SingletonState.h
 * @brief Defines the Singleton template for ensuring single instances of plant states
 */

#ifndef SINGLETONSTATE_H
#define SINGLETONSTATE_H
#include "Plant.h"

/**
 * @class SingletonState
 * @brief Template class implementing the Singleton pattern for PlantState subclasses
 * @tparam T The concrete state class type that should be a singleton
 *
 * This class ensures that only one instance of each plant state exists throughout the
 * application lifecycle. It uses the Curiously Recurring Template Pattern (CRTP) to
 * provide singleton functionality to derived state classes. This approach reduces memory
 * overhead and ensures consistent state behavior across all plants.
 */
template<typename T>
class SingletonState : public PlantState
{

public:

	/**
	 * @brief Gets the singleton instance of the state
	 * @return Reference to the single instance of type T
	 *
	 * Creates the instance on first call using lazy initialization. Thread-safe in C++11
	 * and later due to guaranteed initialization of static local variables.
	 */
    static T& getInstance()
    {
        static T instance;
        return instance;
    }

protected:

	/**
	 * @brief Protected default constructor to prevent direct instantiation
	 */
    SingletonState() = default;

	/**
	 * @brief Protected virtual destructor
	 */
    virtual ~SingletonState() override = default;

	/**
	 * @brief Deleted copy constructor to prevent copying
	 */
    SingletonState(const SingletonState&) = delete;

	/**
	 * @brief Deleted copy assignment operator to prevent copying
	 * @return Reference to this object (deleted)
	 */
    SingletonState& operator=(const SingletonState&) = delete;
};

#endif