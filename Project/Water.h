/**
 * @file Water.h
 * @brief Defines the Water command, a concrete implementation of the Command pattern
 * for watering one or more plants.
 */

#ifndef WATER_H
#define WATER_H

#include "Command.h"
#include <vector>
#include <string>

// Forward declaration of the Plant class, which is the command's receiver
class Plant;

/**
 * @class Water
 * @brief A concrete Command that encapsulates the request to water one or more Plant objects.
 *
 * This command supports undo functionality by storing the moisture level of the
 * plants before the operation.
 */

class Water : public Command 
{

private:

	/**
     * @brief A list of pointers to the Plant objects that will be watered (the receivers).
     */

	std::vector<Plant*> plants;

	/**
     * @brief A parallel list storing the moisture level of each plant *before* the execute operation.
     * This is essential for supporting the undo operation.
     */

	std::vector<int> previousMoisture; 

public:
	/**
     * @brief Constructor for the Water command.
     * @param p A constant reference to a vector of pointers to the Plant objects to be watered.
     */


	Water(const std::vector<Plant*>& p);

	/**
     * @brief Executes the watering action.
     *
     * The current moisture level of each plant is first stored for undo, and then the watering
     * action (e.g., increasing moisture) is performed on each Plant.
     */


	void execute() override;

	/**
     * @brief Undoes the watering action.
     *
     * The moisture level of each plant is reverted to the value stored in `previousMoisture`.
     */

	void undo() override;

	/**
     * @brief Provides a descriptive string for the command.
     * @return A string describing the watering action, including the number of plants affected.
     */

	std::string getDescription() const override;
};

#endif
