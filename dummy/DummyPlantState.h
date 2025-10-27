#ifndef DUMMY_PLANTSTATE_H
#define DUMMY_PLANTSTATE_H

#include <string>

/**
 * @file dummy/DummyPlantState.h
 * @brief Standalone dummy implementation of PlantState for testing
 * @author damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real PlantState implementation
 */

// Forward declaration - we don't need Plant for these dummies
class DummyPlant;

/**
 * @class DummyPlantState
 * @brief Standalone dummy plant state - NO INHERITANCE
 * 
 * Base class for all dummy states. When real PlantState is ready,
 * change these to inherit from PlantState instead.
 */
class DummyPlantState {
public:
    virtual ~DummyPlantState() = default;

    /**
     * @brief Handle time tick
     * @param plant Plant to update
     */
    virtual void onTick(DummyPlant* plant) = 0;

    /**
     * @brief Handle watering
     * @param plant Plant being watered
     */
    virtual void onWater(DummyPlant* plant) = 0;

    /**
     * @brief Check if plant can be sold
     * @return true if plant is in sellable state (MATURE)
     */
    virtual bool canSell() const = 0;

    /**
     * @brief Get state name
     * @return Name of current state
     */
    virtual std::string getStateName() const = 0;
};

/**
 * @class DummyMatureState
 * @brief Dummy MATURE state (plants are ready to sell)
 */
class DummyMatureState : public DummyPlantState {
public:
    void onTick(DummyPlant* plant) override;
    void onWater(DummyPlant* plant) override;
    bool canSell() const override;
    std::string getStateName() const override;
};

/**
 * @class DummySeedlingState
 * @brief Dummy SEEDLING state (plants are not ready)
 */
class DummySeedlingState : public DummyPlantState {
public:
    void onTick(DummyPlant* plant) override;
    void onWater(DummyPlant* plant) override;
    bool canSell() const override;
    std::string getStateName() const override;
};

/**
 * @class DummyGrowingState
 * @brief Dummy GROWING state (plants are still growing)
 */
class DummyGrowingState : public DummyPlantState {
public:
    void onTick(DummyPlant* plant) override;
    void onWater(DummyPlant* plant) override;
    bool canSell() const override;
    std::string getStateName() const override;
};

/**
 * @class DummyWiltingState
 * @brief Dummy WILTING state (plants are sick)
 */
class DummyWiltingState : public DummyPlantState {
public:
    void onTick(DummyPlant* plant) override;
    void onWater(DummyPlant* plant) override;
    bool canSell() const override;
    std::string getStateName() const override;
};

/**
 * @class DummyDeadState
 * @brief Dummy DEAD state (plants are dead - final state)
 */
class DummyDeadState : public DummyPlantState {
public:
    void onTick(DummyPlant* plant) override;
    void onWater(DummyPlant* plant) override;
    bool canSell() const override;
    std::string getStateName() const override;
};

#endif // DUMMY_PLANTSTATE_H