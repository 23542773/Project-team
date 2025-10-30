#ifndef PLANT_H
#define PLANT_H
#include "SoilMix.h"
#include "Pot.h"
#include "CareStrategy.h"
#include "PlantState.h"
#include "PlantFlyweight.h"
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
	
	int check(int change, int low, int high);

public:

	Plant();//Default constructor
	Plant(std::string id, std::string colour, PlantFlyweight* species, CareStrategy* care, PlantState* state, SoilMix* soil, Pot* pot);
	~Plant();
	void water();
	void fertilize();
	void tickDay();
	void addWater(int amount);
	void addHealth(int amount);
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
  	PlantFlyweight* getSpeciesFly();
  	SoilMix* getSoilMix();
  	Pot* getPot();
  	CareStrategy* getCareStrategy();
  	PlantState* getPlantState();


	//Prototype (missing an abstract class)

	Plant(const Plant& other);                  
	Plant* clone(std::string plantId, std::string colour);
};

#endif
