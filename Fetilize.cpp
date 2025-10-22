#include "Fetilize.h"
#include "Greenhouse.h"


Fetilize::Fetilize(Greenhouse& gh) : PlantCommand(gh) {

}

void Fetilize::execute() {
	greenhouse.fertilizeAllPlants();
}
