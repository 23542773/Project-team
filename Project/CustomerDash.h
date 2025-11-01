#ifndef CUSTOMERDASH_H
#define CUSTOMERDASH_H
#include <vector>
#include <string>
#include "NurseryObserver.h"

class CustomerDash : public NurseryObserver 
{
public:

    void onEvent(events::Plant e) override;
    std::vector<std::string>& getMatured();
    void clear();

private:

    std::vector<std::string> maturedIds;
};
#endif
