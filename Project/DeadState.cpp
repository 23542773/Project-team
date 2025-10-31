/**
 * @file DeadState.cpp
 * @brief Implementation of the DeadState class
 */

#include "DeadState.h"

/**
 * @brief Implements state transition logic for dead plants
 *
 * Since this is a terminal state, no transitions occur and no modifications
 * are made to the plant's attributes.
 */
void DeadState::checkChange(Plant&)
{

}

/**
 * @brief Returns the name identifier for this state
 * @return The string "Dead"
 */
std::string DeadState::name()
{
    return "Dead";
}