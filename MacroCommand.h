#ifndef MACRO_COMMAND_H
#define MACRO_COMMAND_H

#include "Command.h"
#include <vector>
#include <memory>
#include <string>

class MacroCommand : public Command 
{
private:

    std::vector<std::unique_ptr<Command>> commands;
    std::string name;
    int executedCount; 
    
public:

    explicit MacroCommand(const std::string& macroName);
    void addCommand(std::unique_ptr<Command> cmd);
    void execute() override;
    void undo() override;
    std::string getDescription() const override;
    size_t size() const;
};

#endif
