/**
 * @file Plant.cpp
 * @brief Implements the Plant class defined in Plant.h.
 * 
 * This file contains the implementation of the Plant class methods, integrating
 * the Flyweight, Strategy, State, and Prototype patterns. Each plant maintains
 * dynamic attributes such as moisture, health, and insecticide level, and
 * interacts with its environment through care strategies and state transitions.
 * 
 * @date 2025-10-31
 */

#include "Plant.h"
#include "DeadState.h"


/// Constructor: initializes all plant components and links shared data.
Plant::Plant(std::string id, std::string colour, PlantFlyweight* species, CareStrategy* care, PlantState* state, SoilMix* soil, Pot* pot)
: plantId(id), colour(colour), species(species), care(care), state(state), soil(soil), pot(pot) {}

/// Destructor: releases owned resources (soil, pot).
Plant::~Plant()
{
	delete soil;
	delete pot;
}

/// Waters the plant using its CareStrategy and checks for state transitions.
void Plant::water()
{
	if(care) care->water(*this);
}

/// Fertilizes the plant using its CareStrategy and checks for state transitions.
void Plant::fertilize()
{
	if(care) care->fertilize(*this);
}

/// Applies insecticide using the CareStrategy and checks for state transitions.
void Plant::sprayInsecticide() 
{
	if(care) care->sprayInsecticide(*this);
}

/// Adds water to the plant, keeping moisture within valid bounds.
void Plant::addWater(int amount)
{
	moistureLevel = check(moistureLevel + amount, 0, 100);
}

/// Adjusts the plant’s health value within valid limits.
void Plant::addHealth(int amount)
{
	health = check(health + amount, 0, 100);
	if(health == 0)
	{
		this->setState(&DeadState::getInstance());
	}
}

/// Modifies the insecticide level, keeping insecticide within valid bounds.
void Plant::addInsecticide(int amount) 
{
    insecticideLevel = check(insecticideLevel + amount, 0, 100);
}

/// Computes the total cost of the plant based on its components.
int Plant::cost()
{
	return species->getCost() + soil->getCost() + pot->getCost();
}

/// Updates the plant’s active liceycle state.
void Plant::setState(PlantState* s)
{
	state = s;
}

/// Returns the plant’s unique identifier.
std::string Plant::id() 
{ 
	return plantId; 
}

/// Returns the species SKU.
std::string Plant::sku() 
{
	 return species->getSku(); 
}

/// Returns the species name
std::string Plant::name() 
{ 
	return species->getName(); 
}

/// Returns the species biome type.
std::string Plant::biome() 
{ 
	return species->getBiome(); 
}

/// Returns the plant’s color.
std::string Plant::getColour() 
{ 
	return colour;
}

/**
 * @brief Calculates the simulated age of the plant in days.
 * 
 * The simulation advances time faster than real-world time; each simulated day
 * corresponds to a fixed number of real seconds.
 * 
 * @return The plant’s age in simulated days.
 */

int Plant::getAgeDays()  
{  
	auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - createdAt).count();
	const double secondsPerSimDay = 10.0;
    return static_cast<int>(diff / (secondsPerSimDay));
}

/// Returns the current moisture level.
int Plant::getMoisture()  
{ 
	return moistureLevel; 
}

/// Returns the plant’s health value.
int Plant::getHealth() 
{ 
	return health; 
}

/// Returns the insecticide level.
int Plant::getInsecticide()  
{ 
	return insecticideLevel; 
}

/// Returns the species flyweight pointer.
PlantFlyweight* Plant::getSpeciesFly() 
{ 
	return species; 
}

/// Returns the soil mix pointer.
SoilMix* Plant::getSoilMix()  
{ 
	return soil; 
}

/// Returns the pot pointer.
Pot* Plant::getPot() 
{ 
	return pot; 
}

/// Returns the care strategy pointer.
CareStrategy* Plant::getCareStrategy()  
{ 
	return care; 
}

/// Returns the plant state pointer.
PlantState*  Plant::getPlantState()    
{ 
	return state; 
}

/**
 * @brief Clamps a value between given low and high bounds.
*/

int Plant::check(int change, int low, int high)
{
	return change < low ? low : (change > high ? high : change);
}

/// Copy constructor used by the Prototype pattern (deep copies soil and pot).
Plant::Plant(const Plant& o) : plantId(o.plantId), colour(o.colour), species(o.species), care(o.care), state(o.state),
soil(o.soil->clone()), pot (o.pot->clone()), ageInDays(o.ageInDays), moistureLevel(o.moistureLevel), health(o.health), createdAt(o.createdAt), insecticideLevel(o.insecticideLevel)
{}

/// Clones the plant with a new ID and color for Prototype-based duplication.
Plant* Plant::clone(std::string newId, std::string col)  
{
    Plant* p = new Plant(*this);  
	p->colour = col;
    p->plantId = std::move(newId);
    p->ageInDays = 0; 
    p->moistureLevel = 0;
    p->health = 100;
	p->insecticideLevel = 100;
	p->createdAt = std::chrono::system_clock::now();
    return p;
}

/**
 * @brief Determines the current simulated season based on the system’s local time.
 * 
 * The mapping is simplified: months 3–5 represent Autumn, 6–8 Winter, 9–11 Spring,
 * and remaining months default to Summer. Used for seasonal plant behavior logic.
 * 
 * @return The current Season value.
 */

Season Plant::currentSeason() 
{
    using namespace std::chrono;
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &t);
#else
    localtime_r(&t, &localTime);
#endif

    int month = localTime.tm_mon + 1; 
    if (month >= 3 && month <= 5)  return Season::Autumn;
    if (month >= 6 && month <= 8)  return Season::Winter;
    if (month >= 9 && month <= 11) return Season::Spring;
    return Season::Summer;
}