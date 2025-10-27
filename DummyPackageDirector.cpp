#include "DummyPackageDirector.h"
#include <iostream>

DummyPackageDirector::DummyPackageDirector(DummyPackageBuilder* builder)
    : builder(builder) {
    std::cout << "[DummyPackageDirector] Created\n";
}

DummyPackageDirector::~DummyPackageDirector() {
}

void DummyPackageDirector::setBuilder(DummyPackageBuilder* newBuilder) {
    builder = newBuilder;
    std::cout << "[DummyPackageDirector] Builder changed\n";
}

void DummyPackageDirector::construct() {
    std::cout << "[DummyPackageDirector] Constructing package...\n";
    
    if (!builder) {
        std::cout << "[DummyPackageDirector] ERROR: No builder set!\n";
        return;
    }
    
    // TODO: Call builder methods in correct sequence
    // builder->reset();
    // builder->buildPlant(...);
    // builder->buildPot(...);
    // builder->buildSoil(...);
    
    std::cout << "[DummyPackageDirector] Package construction complete\n";
}