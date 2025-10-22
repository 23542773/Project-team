#include "Water.h"
#include "Greenhouse.h"


Water::Water(Greenhouse& gh) : PlantCommand(gh) {

}

void Water::execute() {

	greenhouse.waterAllPlants();
}
