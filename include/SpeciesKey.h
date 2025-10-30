#ifndef SPECIESKEY_H
#define SPECIESKEY_H

#include <iostream>

/**
 * @class SpeciesKey
 * @brief Key for identifying plant species variants
 */
class SpeciesKey {

private:
	std::string species;
	std::string variant;

public:
	 bool operator==(const SpeciesKey& other) const;
};

#endif
