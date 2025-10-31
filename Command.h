#ifndef COMMAND_H
#define COMMAND_H
#include <string>


class Command 
{
public:

	virtual ~Command() = default;

	virtual void execute() = 0;
	virtual void undo() {}
	virtual std::string getDescription() const = 0;

	void setUserId(const std::string& uid);
	virtual std::string getUserId() const;

	void setAction(const std::string& act);
	virtual std::string getAction() const;

	void setUndoable(bool u);
	virtual bool isUndoable() const;

private:
	std::string userId;
	std::string action;
	bool undoable = false;
};

#endif
