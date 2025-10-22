#ifndef INVENTORYCOMMAND_H
#define INVENTORYCOMMAND_H

#include "Command.h"

class InventoryService;
class InventoryCommand : public Command {

protected:
    InventoryService& inv;

public:
    InventoryCommand(InventoryService& i);
    virtual void execute() = 0;
};

#endif