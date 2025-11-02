/**
 * @file Fertilize.h
 * @brief Defines the Fertilize command, a concrete implementation of the Command pattern.
 */

#ifndef FERTILIZE_H
#define FERTILIZE_H

#include "Command.h" // Inherits from the Command abstract base class
#include <vector>
#include <string>

// Forward declaration of the Plant class, which is the command's receiver
class Plant;

/**
 * @class Fertilize
 * @brief A concrete Command that encapsulates the request to fertilize one or more Plant objects.
 *
 * This command supports undo functionality by storing the state (health) of the
 * plants before the operation.
 */
class Fertilize : public Command
{

private:

    /**
     * @brief A list of pointers to the Plant objects that will be fertilized (the receivers).
     */
    std::vector<Plant*> plants;

    /**
     * @brief A parallel list storing the health value of each plant *before* the execute operation.
     * This is essential for supporting the undo operation.
     */
    std::vector<int> previousHealth;

public:

    /**
     * @brief Constructor for the Fertilize command.
     * @param p A constant reference to a vector of pointers to the Plant objects to be fertilized.
     */
    Fertilize(const std::vector<Plant*>& p);

    /**
     * @brief Executes the fertilization action.
     *
     * The current health of each plant is first stored for undo, and then the fertilization
     * action (e.g., increasing health) is performed on each Plant.
     */
    void execute() override;

    /**
     * @brief Undoes the fertilization action.
     *
     * The health of each plant is reverted to the value stored in `previousHealth`.
     */
    void undo() override;

    /**
     * @brief Provides a descriptive string for the command.
     * @return A string describing the fertilization action, including the number of plants affected.
     */
    std::string getDescription() const override;
};

#endif