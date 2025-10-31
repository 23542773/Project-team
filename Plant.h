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

class Plant 
{

private:

	std::string plantId;
	std::string colour;

	PlantFlyweight* species;
	CareStrategy* care;
	PlantState* state;
	SoilMix* soil;
	Pot* pot;

	int ageInDays = 0;
	int moistureLevel = 0;
	int health = 100;
	int insecticideLevel = 100; 
	std::chrono::system_clock::time_point createdAt = std::chrono::system_clock::now();
	int check(int change, int low, int high);

public:

	Plant(std::string id, std::string colour, PlantFlyweight* species, CareStrategy* care, PlantState* state, SoilMix* soil, Pot* pot);
	~Plant();
	void water();
	void fertilize();
	void sprayInsecticide();
	void addWater(int amount);
	void addHealth(int amount);
	void addInsecticide(int amount);
	int cost();
	void setState(PlantState* s);

	std::string id();
  	std::string sku();
  	std::string name();
  	std::string biome();
  	std::string getColour();
  	int getAgeDays();
  	int getMoisture();
	int getHealth();
	int getInsecticide();
  	PlantFlyweight* getSpeciesFly();
  	SoilMix* getSoilMix();
  	Pot* getPot();
  	CareStrategy* getCareStrategy();
  	PlantState* getPlantState();
	static Season currentSeason();


	//Prototype (missing an abstract class)

	Plant(const Plant& other);                  
	Plant* clone(std::string plantId, std::string colour);
};

#endif
