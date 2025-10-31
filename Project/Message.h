#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <ctime>

struct Message 
{
    std::string id;       
    std::string fromUser;
    std::string toUser; 
    std::string text;
    std::time_t timestamp; 
};

#endif
