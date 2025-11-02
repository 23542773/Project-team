/**
 * @file GrittyLimeSoilMix.h
 * @brief Defines the GrittyLimeSoilMix class, a concrete SoilMix that acts as a prototype.
 */

#ifndef GRITTYLIMESOILMIX_H
#define GRITTYLIMESOILMIX_H
#include "SoilMix.h"

/**
 * @class GrittyLimeSoilMix
 * @brief A concrete implementation of the SoilMix abstract class, representing a specific type of soil.
 *
 * This class is designed to function as a **Prototype** within a registry, allowing
 * new instances of this soil type to be created via cloning without knowing the
 * details of its construction.
 */

class GrittyLimeSoilMix : public SoilMix
{

public:

	/**
     * @brief Default constructor for GrittyLimeSoilMix.
     */

	GrittyLimeSoilMix();

	/**
     * @brief Provides the human-readable name of this specific soil mix.
     * @return A string containing the name (e.g., "Gritty Lime Soil Mix").
     */

	std::string name() override;
	/**
     * @brief Implements the clone operation required by the Prototype pattern.
     * @return A pointer to a newly created, deep copy of the current GrittyLimeSoilMix object.
     */
	
	SoilMix* clone() const override;
};

#endif
