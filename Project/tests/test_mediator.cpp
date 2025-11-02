/**
 * @file test_mediator.cpp
 * @brief Unit tests for Mediator Pattern data structures
 * @date 2025-11-02
 *
 * Tests the Message structure and StaffRole enumeration used in the Mediator pattern.
 * Note: Full mediator integration testing is not possible due to incomplete
 * Colleague interface implementation in Customer and Staff classes.
 */

// Compatibility fix for older MinGW
#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
#define gmtime_s(a, b) (*a = *gmtime(b), 0)
#endif

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_COLORS_NONE
#include "doctest.h"

#include "../Staff.h"
#include "../Message.h"
#include <ctime>
#include <vector>
#include <string>

// ============================================================================
// TEST 1: MESSAGE STRUCTURE - Message has all required fields
// ============================================================================

TEST_CASE("Message structure - All fields accessible") {
    Message msg;
    msg.id = "MSG001";
    msg.fromUser = "C001";
    msg.toUser = "S001";
    msg.text = "Hello, I need help!";
    msg.timestamp = std::time(nullptr);
    
    CHECK(msg.id == "MSG001");
    CHECK(msg.fromUser == "C001");
    CHECK(msg.toUser == "S001");
    CHECK(msg.text == "Hello, I need help!");
    CHECK(msg.timestamp > 0);
}

// ============================================================================
// TEST 2: MESSAGE TIMESTAMP - Timestamp is current time
// ============================================================================

TEST_CASE("Message - Timestamp reflects message creation time") {
    std::time_t before = std::time(nullptr);
    
    Message msg;
    msg.id = "1";
    msg.fromUser = "User1";
    msg.toUser = "User2";
    msg.text = "Test";
    msg.timestamp = std::time(nullptr);
    
    std::time_t after = std::time(nullptr);
    
    // Timestamp should be between before and after
    CHECK(msg.timestamp >= before);
    CHECK(msg.timestamp <= after);
}

// ============================================================================
// TEST 3: STAFF ROLE ENUMERATION - PlantCare role
// ============================================================================

TEST_CASE("StaffRole - PlantCare enumeration value") {
    StaffRole role = StaffRole::PlantCare;
    CHECK(role == StaffRole::PlantCare);
    CHECK(role != StaffRole::Inventory);
    CHECK(role != StaffRole::Sales);
}

// ============================================================================
// TEST 4: STAFF ROLE ENUMERATION - Inventory role
// ============================================================================

TEST_CASE("StaffRole - Inventory enumeration value") {
    StaffRole role = StaffRole::Inventory;
    CHECK(role == StaffRole::Inventory);
    CHECK(role != StaffRole::PlantCare);
    CHECK(role != StaffRole::Sales);
}

// ============================================================================
// TEST 5: STAFF ROLE ENUMERATION - Sales role
// ============================================================================

TEST_CASE("StaffRole - Sales enumeration value") {
    StaffRole role = StaffRole::Sales;
    CHECK(role == StaffRole::Sales);
    CHECK(role != StaffRole::PlantCare);
    CHECK(role != StaffRole::Inventory);
}

// ============================================================================
// TEST 6: STAFF ROLE COMPARISON - Different roles are not equal
// ============================================================================

TEST_CASE("StaffRole - All three roles are distinct") {
    StaffRole sales = StaffRole::Sales;
    StaffRole inventory = StaffRole::Inventory;
    StaffRole plantCare = StaffRole::PlantCare;
    
    // All roles should be different from each other
    CHECK(sales != inventory);
    CHECK(sales != plantCare);
    CHECK(inventory != plantCare);
    
    // Same roles should be equal
    CHECK(sales == StaffRole::Sales);
    CHECK(inventory == StaffRole::Inventory);
    CHECK(plantCare == StaffRole::PlantCare);
}

// ============================================================================
// TEST 7: MESSAGE COLLECTION - Multiple messages can be stored
// ============================================================================

TEST_CASE("Message - Multiple messages in a collection") {
    std::vector<Message> messages;
    
    Message msg1;
    msg1.id = "1";
    msg1.fromUser = "C001";
    msg1.toUser = "S001";
    msg1.text = "First message";
    msg1.timestamp = std::time(nullptr);
    
    Message msg2;
    msg2.id = "2";
    msg2.fromUser = "S001";
    msg2.toUser = "C001";
    msg2.text = "Reply message";
    msg2.timestamp = std::time(nullptr);
    
    messages.push_back(msg1);
    messages.push_back(msg2);
    
    CHECK(messages.size() == 2);
    CHECK(messages[0].text == "First message");
    CHECK(messages[1].text == "Reply message");
    CHECK(messages[0].fromUser == messages[1].toUser);
    CHECK(messages[0].toUser == messages[1].fromUser);
}

// ============================================================================
// TEST 8: MESSAGE ID - Can use numeric string IDs
// ============================================================================

TEST_CASE("Message - Numeric string IDs") {
    Message msg;
    msg.id = "12345";
    msg.fromUser = "CustomerA";
    msg.toUser = "StaffB";
    msg.text = "Order inquiry";
    msg.timestamp = std::time(nullptr);
    
    CHECK(msg.id == "12345");
    // ID can be converted back to number if needed
    int idNum = std::stoi(msg.id);
    CHECK(idNum == 12345);
}

// ============================================================================
// TEST 9: MESSAGE EMPTY TEXT - Messages can have empty text
// ============================================================================

TEST_CASE("Message - Empty text field") {
    Message msg;
    msg.id = "1";
    msg.fromUser = "User1";
    msg.toUser = "User2";
    msg.text = "";
    msg.timestamp = std::time(nullptr);
    
    CHECK(msg.text.empty());
    CHECK(msg.text == "");
}

// ============================================================================
// TEST 10: MESSAGE LONG TEXT - Messages can have long text
// ============================================================================

TEST_CASE("Message - Long text content") {
    Message msg;
    msg.id = "1";
    msg.fromUser = "C001";
    msg.toUser = "S001";
    msg.text = "This is a very long message that contains a lot of text. ";
    msg.text += "It might be a detailed inquiry about plant care, watering schedules, ";
    msg.text += "fertilizer recommendations, and other important nursery information.";
    msg.timestamp = std::time(nullptr);
    
    CHECK(msg.text.length() > 100);
    CHECK(msg.text.find("plant care") != std::string::npos);
    CHECK(msg.text.find("nursery") != std::string::npos);
}

// ============================================================================
// TEST 11: MESSAGE USER IDS - Different ID formats
// ============================================================================

TEST_CASE("Message - Various user ID formats") {
    Message msg1;
    msg1.id = "1";
    msg1.fromUser = "C001"; // Customer format
    msg1.toUser = "S001";   // Staff format
    msg1.text = "Test";
    msg1.timestamp = std::time(nullptr);
    
    Message msg2;
    msg2.id = "2";
    msg2.fromUser = "STAFF_123";
    msg2.toUser = "CUSTOMER_456";
    msg2.text = "Test";
    msg2.timestamp = std::time(nullptr);
    
    CHECK(msg1.fromUser.length() == 4);
    CHECK(msg1.toUser.length() == 4);
    CHECK(msg2.fromUser.find("STAFF") != std::string::npos);
    CHECK(msg2.toUser.find("CUSTOMER") != std::string::npos);
}

// ============================================================================
// TEST 12: STAFF ROLE ASSIGNMENT - Can assign roles to variables
// ============================================================================

TEST_CASE("StaffRole - Role assignment and comparison") {
    StaffRole role1 = StaffRole::Sales;
    StaffRole role2 = role1;
    
    CHECK(role1 == role2);
    CHECK(role1 == StaffRole::Sales);
    CHECK(role2 == StaffRole::Sales);
    
    role2 = StaffRole::Inventory;
    CHECK(role1 != role2);
    CHECK(role1 == StaffRole::Sales);
    CHECK(role2 == StaffRole::Inventory);
}
