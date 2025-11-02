/**
 * @file MacroCommand.h
 * @brief Defines the MacroCommand class, a concrete Command that aggregates and executes a sequence of other Commands (Composite pattern).
 */

#ifndef MACRO_COMMAND_H
#define MACRO_COMMAND_H

#include "Command.h"
#include <vector>
#include <memory>
#include <string>

/**
 * @class MacroCommand
 * @brief A composite Command that can execute a list of contained Command objects sequentially.
 *
 * This pattern allows clients to treat individual Commands and collections of Commands uniformly.
 * It ensures that execution and undo operations are applied correctly to all sub-commands.
 */

class MacroCommand : public Command 
{
private:
/**
 * @brief The list of concrete Command objects that this macro will execute.
 * Commands are stored as unique pointers for ownership management.
 */

    std::vector<std::unique_ptr<Command>> commands;
    /**
     * @brief A descriptive name for the entire macro operation.
     */

    std::string name;

    /**
     * @brief Tracks the number of sub-commands that were successfully executed during the last `execute()` call.
     * This is crucial for correctly performing the `undo()` operation.
     */

    int executedCount; 
    
public:
/**
 * @brief Constructor for the MacroCommand.
 * @param macroName The human-readable name for this composite command.
 */

    explicit MacroCommand(const std::string& macroName);
    /**
     * @brief Adds a new Command to the sequence of commands to be executed.
     * @param cmd A unique pointer to the Command object to add. The macro takes ownership of the command.
     */

    void addCommand(std::unique_ptr<Command> cmd);
    /**
     * @brief Executes all commands in the `commands` list sequentially.
     *
     * Execution stops if any sub-command fails or throws an exception, and `executedCount` is updated.
     */

    void execute() override;
    /**
     * @brief Undoes the execution of all commands that were successfully executed during the last `execute()` call,
     * typically in reverse order of execution.
     */

    void undo() override;
    /**
     * @brief Provides a descriptive string for the macro command.
     * @return A string combining the macro name and details about the sub-commands.
     */

    std::string getDescription() const override;
    /**
     * @brief Gets the number of sub-commands contained within this macro.
     * @return The number of commands in the sequence.
     */
    
    size_t size() const;
};

#endif
