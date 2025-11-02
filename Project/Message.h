/**
 * @file Message.h
 * @brief Defines the Message structure used for communication between Colleague objects via the Mediator.
 */

#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <ctime>

/**
 * @struct Message
 * @brief A simple data structure encapsulating the necessary information for a chat or system message.
 *
 * This structure serves as the payload passed to the receiveMessage method of Colleague objects.
 */

struct Message 
{
    /**
     * @brief A unique identifier for this message instance.
     */
    std::string id;
    /**
     * @brief The unique ID of the user who sent the message.
     */       
    std::string fromUser;
    /**
     * @brief The unique ID of the user who is the intended recipient of the message.
     */
    std::string toUser; 
    /**
     * @brief The actual content of the message.
     */
    std::string text;
    /**
     * @brief The timestamp indicating when the message was created or sent.
     */
    std::time_t timestamp; 
};

#endif
