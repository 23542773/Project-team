#ifndef MATURESTATE_H
#define MATURESTATE_H
#include "PlantState.h"

class MatureState : public PlantState
{

public:

    static MatureState& getInstance();
    void onTick(Plant& plant) override;
    void checkChange(Plant& plant) override;
    std::string name() override;

protected:

	virtual ~MatureState() override {}
    MatureState();
    MatureState(const MatureState&) {}
    MatureState& operator=(const MatureState&) = delete;
};

#endif
