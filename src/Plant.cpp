#include "Plant.h"

Plant::Plant() 
: plantId(0), colour("dfltColour"), species(NULL), care(NULL), state(NULL), soil(NULL), pot(NULL) {}

Plant::Plant(std::string id, std::string colour, PlantFlyweight* species, CareStrategy* care, PlantState* state, SoilMix* soil, Pot* pot)
: plantId(id), colour(colour), species(species), care(care), state(state), soil(soil), pot(pot) {}

Plant::~Plant()
{
	delete soil;
	delete pot;
}

void Plant::water()
{
	if(care) care->water(*this);
	if(state) state->checkChange(*this);
}
void Plant::fertilize()
{
	if(care) care->fertilize(*this);
	if(state) state->checkChange(*this);
}
void Plant::tickDay()
{
	ageInDays++;
	if(state) 
	{
		state->onTick(*this);
		state->checkChange(*this);
	}

}

void Plant::addWater(int amount)
{
	moistureLevel = check(moistureLevel + amount, 0, 100);
}
void Plant::addHealth(int amount)
{
	health = check(health + amount, 0, 100);
}

int Plant::cost()
{
	return species->getCost() + soil->getCost() + pot->getCost();
}

void Plant::setState(PlantState* s)
{
	state = s;
}

std::string Plant::id() 
{ 
	return plantId; 
}

std::string Plant::sku() 
{
	 return species->getSku(); 
}

std::string Plant::name() 
{ 
	return species->getName(); 
}

std::string Plant::biome() 
{ 
	return species->getBiome(); 
}

std::string Plant::getColour() 
{ 
	return colour;
}

int Plant::getAgeDays()  
{ 
	return ageInDays; 
}

int Plant::getMoisture()  
{ 
	return moistureLevel; 
}

int Plant::getHealth() 
{ 
	return health; 
}

PlantFlyweight* Plant::getSpeciesFly() 
{ 
	return species; 
}

SoilMix* Plant::getSoilMix()  
{ 
	return soil; 
}

Pot* Plant::getPot() 
{ 
	return pot; 
}

CareStrategy* Plant::getCareStrategy()  
{ 
	return care; 
}

PlantState*  Plant::getPlantState()    
{ 
	return state; 
}

int Plant::check(int change, int low, int high)
{
	return change < low ? low : (change > high ? high : change);
}

//Prototype (missing an abstract class)

Plant::Plant(const Plant& o) : plantId(o.plantId), colour(o.colour), species(o.species), care(o.care), state(o.state),
soil(o.soil->clone()), pot (o.pot->clone()), ageInDays(o.ageInDays), moistureLevel(o.moistureLevel), health(o.health) {}

Plant* Plant::clone(std::string newId, std::string col)  
{
    Plant* p = new Plant(*this);  
	p->colour = col;
    p->plantId = std::move(newId);
    p->ageInDays = 0; 
    p->moistureLevel = 0;
    p->health = 100;
    return p;
}
