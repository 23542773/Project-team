#include "ActionLog.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

ActionLog::ActionLog() {}

void ActionLog::appendLog(const std::string& userId, const std::string& action, const std::string& description, bool success, const std::string& extra) 
{
    std::ofstream logFile("../../src/commands.log", std::ios::app);
    if (!logFile.is_open()) 
    {
        std::cerr << "Failed to open command log: commands.log\n";
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif
    std::ostringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    logFile << "[" << timestamp.str() << "] "
            << "User: " << userId << " | "
            << "Action: " << action << " | "
            << "Status: " << (success ? "SUCCESS" : "FAILED") << " | "
            << "Description: " << description;

    if (!extra.empty()) {
        logFile << " | Extra: " << extra;
    }

    logFile << "\n";
    logFile.close();
}

void ActionLog::enqueue(std::unique_ptr<Command> cmd) 
{
    if (!cmd) return;
    appendLog(cmd->getUserId(), cmd->getAction(), "Command enqueued", true, "");
    commandQueue.push(std::move(cmd));
}

bool ActionLog::processNext() 
{
    if (commandQueue.empty()) 
    {
        std::cout << "No commands in queue to process.\n";
        return false;
    }
    
    std::unique_ptr<Command> qcmd = std::move(commandQueue.front());
    commandQueue.pop();
    
    std::string description = qcmd->getDescription();
    bool success = false;
    
    try 
    {
        qcmd->execute();
        success = true;
        
        appendLog(qcmd->getUserId(), qcmd->getAction(), description, true, "");

        if (qcmd->isUndoable())
        {
            restockHistory.push_back(std::move(qcmd));
        }
        
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Command execution failed: " << e.what() << "\n";
        appendLog(qcmd->getUserId(), qcmd->getAction(), description, false, e.what());
    }
    
    return success;
}

int ActionLog::processAll() 
{
    int processed = 0;
    while (!commandQueue.empty()) 
    {
        if (processNext()) {
            processed++;
        }
    }
    return processed;
}

bool ActionLog::undoLastRestock() 
{
    if (restockHistory.empty()) 
    {
        std::cout << "No restock commands to undo.\n";
        return false;
    }
    
    auto& cmd = restockHistory.back();
    std::string description = cmd->getDescription();
    
    try 
    {
        cmd->undo();
        appendLog("SYSTEM", "UNDO RESTOCK", description, true, "Restock undone");
        restockHistory.pop_back();
        return true;
        
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Undo failed: " << e.what() << "\n";
        appendLog("SYSTEM", "UNDO RESTOCK", description, false, e.what());
        return false;
    }
}

size_t ActionLog::queueSize() const 
{
    return commandQueue.size();
}

size_t ActionLog::restockHistorySize() const 
{
    return restockHistory.size();
}
