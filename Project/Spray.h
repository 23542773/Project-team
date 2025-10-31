/**
 * @file Spray.h
 * @brief Declares the Spray command class for applying insecticide to plants.
 * 
 * Implements the Command pattern, allowing spraying actions to be executed and undone.
 * Keeps track of previous insecticide levels for undo functionality.
 * 
 * @date 2025-10-31
 */

#ifndef SPRAY_H
#define SPRAY_H

#include "Command.h"
#include <vector>
#include <string>

class Plant;

/**
 * @class Spray
 * @brief Command for applying insecticide to a group of plants.
 * 
 * Stores a list of target plants and their previous insecticide levels to allow undoing the action.
 */
class Spray : public Command 
{
private:
    /// Plants to apply spray to.
    std::vector<Plant*> plants;

    /// Stores previous insecticide levels for undo functionality.
    std::vector<int> previousInsecticide;

public:

    /**
     * @brief Constructs a Spray command for a list of plants.
     * @param p Vector of Plant pointers to be sprayed.
     */
    Spray(const std::vector<Plant*>& p);

    /**
     * @brief Executes the spray action on all plants.
     */
    void execute() override;

    /**
     * @brief Undoes the spray action, restoring previous insecticide levels.
     */
    void undo() override;

    /**
     * @brief Returns a textual description of this command.
     * @return Description string.
     */
    std::string getDescription() const override;
};

#endif
