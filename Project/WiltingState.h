#ifndef WILTINGSTATE_H
#define WILTINGSTATE_H
#include "PlantState.h"

class WiltingState : public PlantState
{

public:

    static WiltingState& getInstance();
    void checkChange(Plant& plant) override;
    std::string name() override;

protected:

	~WiltingState() override {}
    WiltingState();
    WiltingState(const WiltingState&) {}
    WiltingState& operator=(const WiltingState&) = delete;
};

#endif
