#ifndef DUMMY_PLANT_H
#define DUMMY_PLANT_H

#include <string>

/**
 * @file dummy/DummyPlant.h
 * @brief Standalone dummy implementation of Plant for testing
 * @author damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real Plant implementation
 */

// Forward declarations
class DummyPlantFlyweight;
class DummyPlantState;

/**
 * @class DummyPlant
 * @brief Standalone dummy plant - NO INHERITANCE
 * 
 * When real Plant is ready, simply change this to inherit from Plant.
 */
class DummyPlant {
private:
    std::string id_;
    DummyPlantFlyweight* species_;
    DummyPlantState* state_;
    int ageInDays_;
    int moistureLevel_;

public:
    /**
     * @brief Create dummy plant
     * 
     * @param id Plant ID
     * @param species Species data
     * @param state Initial state
     */
    DummyPlant(const std::string& id,
               DummyPlantFlyweight* species,
               DummyPlantState* state);

    ~DummyPlant();

    // ====== GETTERS ======

    /**
     * @brief Get plant ID
     * @return Plant identifier
     */
    std::string getId() const;

    /**
     * @brief Get species data
     * @return Pointer to DummyPlantFlyweight
     */
    DummyPlantFlyweight* getSpecies() const;

    /**
     * @brief Get current state
     * @return Pointer to current DummyPlantState
     */
    DummyPlantState* getState() const;

    /**
     * @brief Get age in days
     * @return Age
     */
    int getAgeInDays() const;

    /**
     * @brief Get moisture level
     * @return Current moisture level (0-100)
     */
    int getMoistureLevel() const;

    // ====== SETTERS ======

    /**
     * @brief Set plant state
     * @param newState New state to set
     */
    void setState(DummyPlantState* newState);

    /**
     * @brief Set moisture level
     * @param level New moisture level
     */
    void setMoistureLevel(int level);

    // ====== OPERATIONS ======

    /**
     * @brief Water the plant
     */
    void water();

    /**
     * @brief Fertilize the plant
     */
    void fertilize();

    /**
     * @brief Advance time by one day
     */
    void tickDay();

    /**
     * @brief Check if plant can be sold
     * @return true if state->canSell() returns true
     */
    bool canBeSold() const;
};

#endif // DUMMY_PLANT_H