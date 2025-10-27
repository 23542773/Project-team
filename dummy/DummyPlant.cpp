#include "DummyPlant.h"
#include "DummyPlantFlyweight.h"
#include "DummyPlantState.h"
#include <iostream>

DummyPlant::DummyPlant(const std::string& id,
                       DummyPlantFlyweight* species,
                       DummyPlantState* state)
    : id_(id),
      species_(species),
      state_(state),
      ageInDays_(0),
      moistureLevel_(50) {
    std::cout << "[DummyPlant] Created: " << id << "\n";
}

DummyPlant::~DummyPlant() {
    std::cout << "[DummyPlant] Destroyed: " << id_ << "\n";
}

std::string DummyPlant::getId() const {
    return id_;
}

DummyPlantFlyweight* DummyPlant::getSpecies() const {
    return species_;
}

DummyPlantState* DummyPlant::getState() const {
    return state_;
}

int DummyPlant::getAgeInDays() const {
    return ageInDays_;
}

int DummyPlant::getMoistureLevel() const {
    return moistureLevel_;
}

void DummyPlant::setState(DummyPlantState* newState) {
    state_ = newState;
    std::cout << "[DummyPlant] " << id_ << " state changed\n";
}

void DummyPlant::setMoistureLevel(int level) {
    if (level < 0) moistureLevel_ = 0;
    else if (level > 100) moistureLevel_ = 100;
    else moistureLevel_ = level;
}

void DummyPlant::water() {
    std::cout << "[DummyPlant] " << id_ << " watered\n";
    moistureLevel_ += 20;
    if (moistureLevel_ > 100) moistureLevel_ = 100;
}

void DummyPlant::fertilize() {
    std::cout << "[DummyPlant] " << id_ << " fertilized\n";
}

void DummyPlant::tickDay() {
    ageInDays_++;
    std::cout << "[DummyPlant] " << id_ << " aged to " << ageInDays_ << " days\n";
}

bool DummyPlant::canBeSold() const {
    if (state_) {
        return state_->canSell();
    }
    return false;
}