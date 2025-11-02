/**
 * @file Command.h
 * @brief Defines the abstract base class Command, which is the core of the Command design pattern.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>

/**
 * @class Command
 * @brief An abstract class that declares an interface for executing an operation.
 *
 * This class encapsulates a request as an object, thereby letting you parameterize
 * clients with different requests, queue or log requests, and support undoable operations.
 */
class Command
{
public:

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived command classes.
     */
    virtual ~Command() = default;

    /**
     * @brief Executes the command's core operation.
     *
     * This is a pure virtual function and must be implemented by concrete subclasses.
     */
    virtual void execute() = 0;

    /**
     * @brief Undoes the effect of a previously executed command.
     *
     * This method provides a default empty implementation for commands that are not undoable.
     * Concrete subclasses should override this if they support undo.
     */
    virtual void undo() {}

    /**
     * @brief Gets a human-readable description of the command's intent or action.
     *
     * This is a pure virtual function and must be implemented by concrete subclasses.
     *
     * @return A string describing the command (e.g., "Restock 5 units of product X").
     */
    virtual std::string getDescription() const = 0;

    /**
     * @brief Sets the ID of the user who initiated this command.
     * @param uid The user ID string.
     */
    void setUserId(const std::string& uid);

    /**
     * @brief Gets the ID of the user associated with this command.
     * @return The user ID string.
     */
    virtual std::string getUserId() const;

    /**
     * @brief Sets a short, categorical name for the action (e.g., "RESTOCK", "SALE").
     * @param act The action string.
     */
    void setAction(const std::string& act);

    /**
     * @brief Gets the short action name of this command.
     * @return The action string.
     */
    virtual std::string getAction() const;

    /**
     * @brief Sets whether the command supports the undo operation.
     * @param u True if the command is undoable, false otherwise.
     */
    void setUndoable(bool u);

    /**
     * @brief Checks if the command supports the undo operation.
     * @return True if the command is marked as undoable, false otherwise.
     */
    virtual bool isUndoable() const;

private:
    /**
     * @brief Stores the ID of the user who initiated the command.
     */
    std::string userId;

    /**
     * @brief Stores a categorical identifier for the action.
     */
    std::string action;

    /**
     * @brief Flag indicating whether the command can be undone. Defaults to false.
     */
    bool undoable = false;
};

#endif