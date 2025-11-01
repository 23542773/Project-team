#ifndef STAFFDASH_H
#define STAFFDASH_H
#include <vector>
#include <string>
#include "NurseryObserver.h"

class StaffDash : public NurseryObserver 
{
public:

    void onEvent(events::Plant e) override;
    void onEvent(events::Stock s) override;
    void onEvent(events::Order& o) override;
    std::vector<std::string>& getAlerts();
    void clear();

private:

    std::vector<std::string> alerts;
};
#endif
