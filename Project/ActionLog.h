/**
 * @file ActionLog.h
 * @brief Defines the ActionLog class for managing and processing a queue of Command objects,
 * along with a history of successful "restock" commands for undo functionality.
 */

#ifndef ACTION_LOG_H
#define ACTION_LOG_H

#include "Command.h"
#include <memory>
#include <queue>
#include <vector>
#include <string>

/**
 * @class ActionLog
 * @brief Manages a queue of commands and a history of executed restock commands.
 *
 * This class uses the Command design pattern to queue up actions, process them sequentially,
 * and maintain a history for a specific type of command (restock) to allow for an undo operation.
 */
class ActionLog
{

private:

    /**
     * @brief The queue holding commands waiting to be processed.
     *
     * Commands are stored as unique pointers to manage their lifecycle.
     */
    std::queue<std::unique_ptr<Command>> commandQueue;

    /**
     * @brief History of successfully executed 'restock' commands.
     *
     * This history is used to facilitate the undoLastRestock functionality.
     */
    std::vector<std::unique_ptr<Command>> restockHistory;

    /**
     * @brief Appends an entry to an internal log (implementation assumed elsewhere).
     * @param userId The ID of the user performing the action.
     * @param action A brief name for the action (e.g., "RESTOCK", "SALE").
     * @param description A detailed description of the action.
     * @param success True if the action was successful, false otherwise.
     * @param extra Optional extra information to be logged. Defaults to an empty string.
     */
    void appendLog(const std::string& userId, const std::string& action, const std::string& description, bool success, const std::string& extra = "");

public:

    /**
     * @brief Default constructor for ActionLog.
     */
    ActionLog();

    /**
     * @brief Default destructor for ActionLog.
     */
    ~ActionLog() = default;

    /**
     * @brief Adds a command to the back of the processing queue.
     * @param cmd A unique pointer to the Command object to be queued.
     */
    void enqueue(std::unique_ptr<Command> cmd);

    /**
     * @brief Processes the next command at the front of the queue.
     *
     * If successful, the command is executed. If the command is a restock command,
     * it is moved to the restock history for potential undo.
     *
     * @return true if a command was successfully processed (executed), false if the queue was empty or execution failed.
     */
    bool processNext();

    /**
     * @brief Processes all commands currently in the queue.
     * @return The number of commands that were successfully processed (executed).
     */
    int processAll();

    /**
     * @brief Undoes the effect of the last successfully executed restock command.
     *
     * This requires the Command object to implement an `undo()` method.
     *
     * @return true if an undo operation was performed, false if the history is empty or undo failed.
     */
    bool undoLastRestock();

    /**
     * @brief Gets the current size of the command queue.
     * @return The number of commands waiting to be processed.
     */
    size_t queueSize() const;

    /**
     * @brief Gets the current size of the restock history vector.
     * @return The number of restock commands in the history.
     */
    size_t restockHistorySize() const;
};

#endif