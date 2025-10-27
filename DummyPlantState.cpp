#include "DummyPlantState.h"
#include "DummyPlant.h"
#include <iostream>

// ====== MATURE STATE ======
void DummyMatureState::onTick(DummyPlant* plant) {
    // TODO: Dummy implementation
    std::cout << "[DummyMatureState::onTick] Plant aged one day\n";
}

void DummyMatureState::onWater(DummyPlant* plant) {
    // TODO: Dummy implementation
    std::cout << "[DummyMatureState::onWater] Plant watered\n";
}

bool DummyMatureState::canSell() const {
    // IMPORTANT: This is what facade checks!
    return true;  // TODO: MATURE can be sold
}

std::string DummyMatureState::getStateName() const {
    return "Mature";
}

// ====== SEEDLING STATE ======
void DummySeedlingState::onTick(DummyPlant* plant) {
    std::cout << "[DummySeedlingState::onTick] Seedling growing\n";
}

void DummySeedlingState::onWater(DummyPlant* plant) {
    std::cout << "[DummySeedlingState::onWater] Seedling watered carefully\n";
}

bool DummySeedlingState::canSell() const {
    // TODO: IMPORTANT: Seedlings cannot be sold
    return false;
}

std::string DummySeedlingState::getStateName() const {
    return "Seedling";
}

// ====== GROWING STATE ======
void DummyGrowingState::onTick(DummyPlant* plant) {
    std::cout << "[DummyGrowingState::onTick] Plant growing\n";
}

void DummyGrowingState::onWater(DummyPlant* plant) {
    std::cout << "[DummyGrowingState::onWater] Plant watered\n";
}

bool DummyGrowingState::canSell() const {
    // TODO: Growing plants not ready yet
    return false;
}

std::string DummyGrowingState::getStateName() const {
    return "Growing";
}

// ====== WILTING STATE ======
void DummyWiltingState::onTick(DummyPlant* plant) {
    std::cout << "[DummyWiltingState::onTick] Plant wilting more\n";
}

void DummyWiltingState::onWater(DummyPlant* plant) {
    std::cout << "[DummyWiltingState::onWater] Attempting to revive wilting plant\n";
}

bool DummyWiltingState::canSell() const {
    // TODO: Cannot sell wilting plants
    return false;
}

std::string DummyWiltingState::getStateName() const {
    return "Wilting";
}

// ====== DEAD STATE ======
void DummyDeadState::onTick(DummyPlant* plant) {
    std::cout << "[DummyDeadState::onTick] Plant is dead (no changes)\n";
}

void DummyDeadState::onWater(DummyPlant* plant) {
    std::cout << "[DummyDeadState::onWater] Dead plant cannot be watered\n";
}

bool DummyDeadState::canSell() const {
    // TODO: Cannot sell dead plants
    return false;
}

std::string DummyDeadState::getStateName() const {
    return "Dead";
}