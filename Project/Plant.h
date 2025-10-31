/**
 * @file Plant.h
 * @brief Declares the Plant class, representing an individual plant instance within the greenhouse system.
 * 
 * The Plant class composes multiple pattern-based components including:
 * - **Flyweight (PlantFlyweight): Shares intrinsic species data.
 * - **Strategy (CareStrategy): Encapsulates biome-specific care behavior (e.g., watering, fertilizing).
 * - **State (PlantState): Tracks and transitions between growth stages.
 * - **Prototype: Enables efficient cloning of existing plants.
 * 
 * Each plant maintains its own mutable attributes such as moisture, health, and insecticide levels,
 * while delegating fixed species data to shared flyweights. Time-based simulation enables plants to age
 * dynamically and respond to environmental care routines.
 * 
 * @date 2025-10-31
 * @author
 * Project Teams
 */

#ifndef PLANT_H
#define PLANT_H
#include "SoilMix.h"
#include "Pot.h"
#include "CareStrategy.h"
#include "PlantState.h"
#include "PlantFlyweight.h"
#include <chrono>
class PlantState;
class CareStrategy;
class PlantFlyweight;

/**
 * @class Plant
 * @brief Represents a single plant entity in the greenhouse system.
 * 
 * A Plant instance combines shared intrinsic species data (via Flyweight) with
 * its own extrinsic state (moisture, health, etc.). It reacts to external care
 * actions using Strategy and updates its growth phase using the State pattern.
 * The Prototype pattern supports efficient cloning of plant objects for reuse
 * or replication.
 */

class Plant 
{

private:

	/// Unique identifier for the plant.
	std::string plantId;

	/// Color of the plant
	std::string colour;

	/// Shared species data (Flyweight).
	PlantFlyweight* species;

	/// Strategy defining biome-specific care behavior.
	CareStrategy* care;

	/// Current lifecycle state.
	PlantState* state;

	/// Composition of the plant's soil type.
	SoilMix* soil;

	/// Type of pot the plant is grown in.
	Pot* pot;

	/// Age of the plant in days.
	int ageInDays = 0;

	/// Current moisture level (0-100).
	int moistureLevel = 0;

	/// Current health level (0-100).
	int health = 100;

	/// Current insecticide level (0-100).
	int insecticideLevel = 100; 

	/// Creation timestamp.
	std::chrono::system_clock::time_point createdAt = std::chrono::system_clock::now();

	/**
     * @brief Constrains a value within a given range.
     * @param change The input value to check.
     * @param low The lower bound.
     * @param high The upper bound.
     * @return The clamped value between @p low and @p high.
     */
	int check(int change, int low, int high);

public:

	/**
     * @brief Constructs a new Plant instance.
     * @param id Unique plant identifier.
     * @param colour The color of the plant.
     * @param species Pointer to the plant’s flyweight species object.
     * @param care Pointer to the care strategy used for maintenance.
     * @param state Pointer to the plant’s current lifecycle state.
     * @param soil Pointer to the soil mix used.
     * @param pot Pointer to the pot used.
     */
	Plant(std::string id, std::string colour, PlantFlyweight* species, CareStrategy* care, PlantState* state, SoilMix* soil, Pot* pot);

	/// Destructor: cleans up owned resources (soil, pot).
	~Plant();

	/** @brief Performs watering according to the active CareStrategy. */
	void water();

	/** @brief Performs fertilization according to the active CareStrategy. */
	void fertilize();

	/** @brief Applies insecticide according to the active CareStrategy. */
	void sprayInsecticide();

	/** @brief Increases or decreases moisture level, clamped between 0 and 100. */
	void addWater(int amount);

	/** @brief Increases or decreases health, clamped between 0 and 100. */
	void addHealth(int amount);

	/** @brief Increases or decreases insecticide level, clamped between 0 and 100. */
	void addInsecticide(int amount);

	/**
     * @brief Calculates the total cost of this plant.
     * @return The combined cost of species, soil, and pot.
     */
	int cost();

	/** @brief Updates the plant’s current lifecycle state. */
	void setState(PlantState* s);

	/// Returns the plant’s unique ID.
	std::string id();

  	/// Returns the species SKU from the Flyweight.
  	std::string sku();

  	/// Returns the species name.
  	std::string name();

	/// Returns the species’ biome type.
  	std::string biome();

	/// Returns the plant’s color.
  	std::string getColour();

	/// Returns the plant’s simulated age in days.
  	int getAgeDays();

	/// Returns the current moisture level.
  	int getMoisture();

	/// Returns the plant’s current health value.
	int getHealth();

	/// Returns the current insecticide level.
	int getInsecticide();

	/// Returns the associated PlantFlyweight pointer.
  	PlantFlyweight* getSpeciesFly();

	/// Returns the associated SoilMix pointer.
  	SoilMix* getSoilMix();

	/// Returns the associated Pot pointer.
  	Pot* getPot();

	/// Returns the associated CareStrategy pointer.
  	CareStrategy* getCareStrategy();

	/// Returns the associated PlantState pointer.
  	PlantState* getPlantState();

	/**
     * @brief Returns the current simulated season based on local time.
     * @return The current Season enum value.
     */
	static Season currentSeason();


	/**
     * @brief Copy constructor (supports Prototype behavior).
     * Performs a deep copy of owned resources (soil, pot).
     * @param other The plant to copy from.
     */

	Plant(const Plant& other);      
	
	/**
     * @brief Creates a cloned copy of this plant with a new ID and color.
     * @param plantId New plant identifier.
     * @param colour New color variation.
     * @return Pointer to the newly cloned plant instance.
     */
	Plant* clone(std::string plantId, std::string colour);
};

#endif
