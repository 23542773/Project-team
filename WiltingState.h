#ifndef WILTINGSTATE_H
#define WILTINGSTATE_H
#include "PlantState.h"

class WiltingState : public PlantState
{

public:

    static WiltingState& getInstance();
    void onTick(Plant& plant) override;
    void checkChange(Plant& plant) override;
    std::string name() const override;

protected:

	~WiltingState() override {}
    WiltingState();
    WiltingState(const WiltingState&) {}
    WiltingState& operator=(const WiltingState&) = delete;
};

#endif
