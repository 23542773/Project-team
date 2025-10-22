#ifndef SPECIESKEY_H
#define SPECIESKEY_H

#include <iostream>

class SpeciesKey {

private:
	std::string species;
	std::string variant;

public:
	bool operator==(SpeciesKey& s);
};

#endif
