#ifndef DEADSTATE_H
#define DEADSTATE_H
#include "PlantState.h"

class DeadState : public PlantState
{

public:

    static DeadState& getInstance();
    void onTick(Plant& plant) override;
    void checkChange(Plant& plant) override;
    std::string name() override;

protected:

	virtual ~DeadState() override {}
    DeadState();
    DeadState(const DeadState&) {}
    DeadState& operator=(const DeadState&) = delete;
};

#endif
