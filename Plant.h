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

	Plant(std::string id, std::string colour, PlantFlyweight* species, CareStrategy* care, PlantState* state, SoilMix* soil, Pot* pot);
	~Plant();
	void water();
	void fertilize();
	void tickDay();
	void addWater(int amount);
	void addHealth(int amount);
	int cost();
	void setState(PlantState* s);

	std::string id() const;
  	std::string sku() const;
  	std::string name()const;
  	std::string biome()const;
  	std::string getColour()const;
  	int getAgeDays() const;
  	int getMoisture()const;
	int getHealth()const;
  	PlantFlyweight* getSpeciesFly() const;
  	SoilMix* getSoilMix() const;
  	Pot* getPot() const;
  	CareStrategy* getCareStrategy() const;
  	PlantState* getPlantState() const;


	//Prototype (missing an abstract class)

	Plant(const Plant& other);                  
	Plant* clone(std::string plantId, std::string colour);
};

#endif
