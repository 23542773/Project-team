#ifndef ACTION_LOG_H
#define ACTION_LOG_H

#include "Command.h"
#include <memory>
#include <queue>
#include <vector>
#include <string>

class ActionLog 
{

private:

    std::queue<std::unique_ptr<Command>> commandQueue;
    std::vector<std::unique_ptr<Command>> restockHistory;

    void appendLog(const std::string& userId, const std::string& action, const std::string& description, bool success, const std::string& extra = "");
    
public:

    ActionLog();
    ~ActionLog() = default;
    
    void enqueue(std::unique_ptr<Command> cmd);
    
    bool processNext();
    
    int processAll();
    
    bool undoLastRestock();

    size_t queueSize() const;
    
    size_t restockHistorySize() const;
};

#endif
