#include "Command.h"

void Command::setUserId(const std::string& uid) 
{
    userId = uid; 
    
}

std::string Command::getUserId() const 
{ 
    return userId; 
}

void Command::setAction(const std::string& act) 
{ 
    action = act;
 }
std::string Command::getAction() const 
{ 
    return action; 
}

void Command::setUndoable(bool u) 
{
     undoable = u; 
}
 bool Command::isUndoable() const 
 { 
    return undoable; 
}