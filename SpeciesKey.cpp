#include "SpeciesKey.h"

bool SpeciesKey::operator==(const SpeciesKey& other) const { return (species==other.species) && (variant==other.variant); }
