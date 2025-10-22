#include "Restock.h"
#include "Greenhouse.h"


Restock::Restock(Greenhouse& gh) : PlantCommand(gh) {

}

void Restock::execute() {

	greenhouse.restockPlants();
}
