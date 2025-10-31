#include "MacroCommand.h"
#include <iostream>
#include <sstream>

MacroCommand::MacroCommand(const std::string& macroName) : name(macroName), executedCount(0) {}

void MacroCommand::addCommand(std::unique_ptr<Command> cmd) 
{
    if (cmd) 
    {
        commands.push_back(std::move(cmd));
    }
}

void MacroCommand::execute() 
{
    executedCount = 0;
    for (auto& cmd : commands) 
    {
        if (cmd) 
        {
            try 
            {
                cmd->execute();
                executedCount++;
            } 
            catch (const std::exception& e) 
            {
                std::cerr << "Sub-command failed in macro '" << name << "': " << e.what() << "\n";
                std::cerr << "Rolling back " << executedCount << " executed command(s)...\n";
                for (int i = executedCount - 1; i >= 0; --i) 
                {
                    try 
                    {
                        commands[i]->undo();
                    } 
                    catch (const std::exception& undoEx) 
                    {
                        std::cerr << "Rollback failed for sub-command " << i << ": " << undoEx.what() << "\n";
                    }
                }
                
                throw;
            }
        }
    }
    
}

void MacroCommand::undo() 
{
    
    for (int i = static_cast<int>(commands.size()) - 1; i >= 0; --i) 
    {
        if (commands[i]) 
        {
            try 
            {
                commands[i]->undo();
            } 
            catch (const std::exception& e) 
            {
                std::cerr << "Undo failed for sub-command " << i << " in macro '" << name << "': " << e.what() << "\n";
            }
        }
    }
}

std::string MacroCommand::getDescription() const 
{
    std::ostringstream oss;
    oss << "Macro: " << name << " [" << commands.size() << " commands";
    
    if (executedCount > 0 && executedCount < commands.size()) 
    {
        oss << ", " << executedCount << " executed";
    }  
    oss << "]";
    return oss.str();
}

size_t MacroCommand::size() const 
{ 
    return commands.size(); 
}
