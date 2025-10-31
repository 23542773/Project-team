#include "Plant.h"

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

void Plant::sprayInsecticide() 
{
	if(care) care->sprayInsecticide(*this);
	if(state) state->checkChange(*this);
}

void Plant::addWater(int amount)
{
	moistureLevel = check(moistureLevel + amount, 0, 100);
}

void Plant::addHealth(int amount)
{
	health = check(health + amount, 0, 100);
}

void Plant::addInsecticide(int amount) 
{
    insecticideLevel = check(insecticideLevel + amount, 0, 100);
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
	auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - createdAt).count();
	const double secondsPerSimDay = 10.0;
    return static_cast<int>(diff / (secondsPerSimDay));
}

int Plant::getMoisture()  
{ 
	return moistureLevel; 
}

int Plant::getHealth() 
{ 
	return health; 
}

int Plant::getInsecticide()  
{ 
	return insecticideLevel; 
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
soil(o.soil->clone()), pot (o.pot->clone()), ageInDays(o.ageInDays), moistureLevel(o.moistureLevel), health(o.health), createdAt(o.createdAt), insecticideLevel(o.insecticideLevel)
{}

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
    return Season::Winter;
}