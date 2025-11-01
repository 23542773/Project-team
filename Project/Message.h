/**
 * @file Message.h
 * @brief Defines the Message data structure for inter-colleague communication
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <ctime>

/**
 * @struct Message
 * @brief Data structure representing a message between colleagues
 *
 * This structure encapsulates all information about a message sent through
 * the mediator system. Messages are created by the ChatMediator and delivered
 * to both sender and recipient for conversation history tracking.
 *
 * Each message has a unique ID, sender and recipient identifiers, the message
 * content, and a timestamp for chronological ordering.
 */
struct Message 
{
    /// Unique identifier for this message (sequence number)
    std::string id;

    /// User ID of the message sender
    std::string fromUser;

    /// User ID of the message recipient
    std::string toUser;

    /// The text content of the message
    std::string text;

    /// Timestamp when the message was sent (Unix time)
    std::time_t timestamp; 
};

#endif
