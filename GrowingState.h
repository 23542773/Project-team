#ifndef GROWINGSTATE_H
#define GROWINGSTATE_H
#include "PlantState.h"

class GrowingState : public PlantState 
{
public:

    static GrowingState& getInstance();
    void onTick(Plant& plant) override;
    void checkChange(Plant& plant) override;
    std::string name() override;

protected:

	virtual ~GrowingState() override {}
    GrowingState();
    GrowingState(const GrowingState&) {}
    GrowingState& operator=(const GrowingState&) = delete;
};
#endif