#ifndef CUSTOMRPLANTPACKAGE_H
#define CUSTOMRPLANTPACKAGE_H

/*
#include "Plant"
#inlcude "Pot"
#include "SoilMix"
Just add the include so long
before having the files
*/
//this is the product. Save the 
//informationn gotten from the 
//factory here
class CustomPlantPackage{
    private:
    Plant* plant;
    Pot* pot;
    SoilMix* soil;
};

#endif // CUSTOMRPLANTPACKAGE_H