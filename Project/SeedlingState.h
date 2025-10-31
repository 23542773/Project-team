#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H
#include "PlantState.h"

class SeedlingState : public PlantState 
{
public:

    static SeedlingState& getInstance();
    void checkChange(Plant& plant) override;
    std::string name() override;

protected:

	virtual ~SeedlingState() override {}
    SeedlingState();
    SeedlingState(const SeedlingState&) {}
    SeedlingState& operator=(const SeedlingState&) = delete;
};
#endif
