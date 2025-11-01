/**
 * @file NurseryFacade.h
 * @brief Defines the NurseryFacade class for simplified nursery management
 * @date 2025-10-31
 * @author Project Teams
 */


#ifndef NURSERY_FACADE_H
#define NURSERY_FACADE_H
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include "Events.h"
#include <memory>
#include "PlantFlyweight.h"
#include "SalesService.h"
#include "StaffService.h"
#include "ActionLog.h"

class InventoryService;
class SalesService;
class StaffService;
class Greenhouse;
class SpeciesCatalog;
class PlantRegistry;
class Plant;
class CustomerService;
class Staff;
class Customer;
class ActionLog;

/**
 * @class NurseryFacade
 * @brief Unified interface for all nursery management operations
 * 
 * Provides a simplified API for inventory, sales, staff, customer, and greenhouse operations.
 * Aggregates multiple subsystems into a cohesive interface.
 */
class NurseryFacade 
{
public:

    /**
     * @brief Construct the facade with all required subsystem dependencies
     * @param inv Inventory service for plant availability tracking
     * @param sales Sales service for order and receipt management
     * @param staff Staff service for employee and task management
     * @param customers Customer service for client management
     * @param greenhouse Greenhouse for plant lifecycle and state management
     * @param catalog Species catalog for plant species metadata
     * @param invoker Command pattern invoker for queued and undoable operations
     */
    NurseryFacade(InventoryService* inv, SalesService* sales, StaffService* staff, CustomerService* customers, Greenhouse* greenhouse,
    SpeciesCatalog* catalog, ActionLog* invoker);
    
    /**
     * @brief Get all plants currently available for purchase
     * @return Vector of pointers to available plants
     */
    std::vector<Plant*> browseAvailable();

    /**
     * @brief Process a customer checkout transaction
     * @param customerId Unique identifier for the customer
     * @param lines Vector of order line items (plant ID, SKU, description, cost)
     * @param amountPaid Payment amount tendered by customer
     * @return Receipt structure with success status, order ID, totals, and change
     */
    struct Receipt checkout(std::string customerId, std::vector<events::OrderLine>& lines, double amountPaid);

    /**
     * @brief Retrieve all receipts for a specific customer
     * @param customerId Customer identifier
     * @return Vector of receipts associated with the customer
     */
    std::vector<struct Receipt> getCustomerReceipts(std::string customerId);

    /**
     * @brief Get a specific plant by its unique identifier
     * @param id Plant identifier
     * @return Pointer to the plant, or nullptr if not found
     */
    Plant* getPlant(std::string id);

    /**
     * @brief Get all orders placed by a specific customer
     * @param customerId Customer identifier
     * @return Vector of order events for the customer
     */
    std::vector<events::Order> getCustomerOrders(std::string customerId);

    /**
     * @brief Get all orders assigned to a specific staff member
     * @param staffId Staff identifier
     * @return Vector of order events assigned to the staff member
     */
    std::vector<events::Order> getStaffOrders(std::string staffId);

    /**
     * @brief List all registered staff members
     * @return Vector of staff objects with ID, name, role, and assigned orders
     */
    std::vector<Staff> listAllStaff();

    /**
     * @brief List all registered customers
     * @return Vector of customer objects with ID and name
     */
    std::vector<Customer> listAllCustomers();

    /**
     * @brief List all plant species available in the catalog
     * @return Vector of shared pointers to species flyweight objects
     */
    std::vector<std::shared_ptr<PlantFlyweight>> listAllSpecies();

    /**
     * @brief Get the current quantity of plants for a given species
     * @param sku Species SKU
     * @return Number of plants of this species in the greenhouse
     */
    int getSpeciesQuantity(std::string sku);

    /**
     * @brief List all plants in the greenhouse (regardless of availability)
     * @return Vector of pointers to all plants
     */
    std::vector<Plant*> listAllPlants();

    /**
     * @brief Directly water a set of plants (executes immediately, not queued)
     * @param plants Vector of plant pointers to water
     */
    void waterPlants(std::vector<Plant*>& plants);

    /**
     * @brief Directly fertilize a set of plants (executes immediately, not queued)
     * @param plants Vector of plant pointers to fertilize
     */
    void fertilizePlants(std::vector<Plant*>& plants);

    /**
     * @brief Directly spray insecticide on a set of plants (executes immediately, not queued)
     * @param plants Vector of plant pointers to spray
     */
    void sprayInsecticide(std::vector<Plant*>& plants);

    /**
     * @brief Advance time for all plants, triggering state transitions and observer notifications
     * 
     * Each tick:
     * - Increments plant age
     * - Checks for state changes (Seedling -> Growing -> Mature -> Wilting -> Dead)
     * - Notifies observers on state transitions
     * - Removes dead plants from greenhouse
     */
    void tickAllPlants();

    /**
     * @brief Execute morning care routine: water (3x) + fertilize (1x)
     * @param plants Vector of plants to apply routine to
     */
    void runMorningRoutine(std::vector<Plant*>& plants);
    
    /**
     * @brief Execute night care routine: water (1x) + spray insecticide (2x)
     * @param plants Vector of plants to apply routine to
     */
    void runNightRoutine(std::vector<Plant*>& plants);
    
    /**
     * @brief Emergency care for all wilting plants: fertilize (3x) + water (2x) + spray (2x)
     * 
     * Automatically identifies wilting plants and applies intensive care macro command.
     */
    void runUrgentCare();

    /**
     * @brief Check if a customer ID is registered
     * @param id Customer identifier
     * @return True if customer exists, false otherwise
     */
    bool isValidCustomer(std::string id);

    /**
     * @brief Check if a staff ID is registered
     * @param id Staff identifier
     * @return True if staff member exists, false otherwise
     */
    bool isValidStaff(std::string id);

    /**
     * @brief Mark an order as completed, sell plants, and remove from greenhouse
     * @param orderId Order identifier
     * @return True if order was successfully completed, false if not found or already completed
     */
    bool completeOrder(std::string orderId);

    /**
     * @brief Get message history between two users (staff-to-staff or staff-to-customer)
     * @param userA First user identifier
     * @param userB Second user identifier
     * @return Vector of messages exchanged between the two users, ordered by timestamp
     */
    std::vector<struct Message> getConversation(const std::string& userA, const std::string& userB);

    /**
     * @brief Get a customer object by ID
     * @param id Customer identifier
     * @return Pointer to customer, or nullptr if not found
     */
    Customer* getCustomer(std::string id);

    /**
     * @brief Get a staff object by ID
     * @param id Staff identifier
     * @return Pointer to staff member, or nullptr if not found
     */
    Staff* getStaff(std::string id);

    /**
     * @brief Generate personalized plant recommendations for a customer
     * 
     * Algorithm:
     * - No order history: Seasonal plants + random selection (up to 15 plants)
     * - With order history: Favorite biome -> Seasonal -> Similar care profiles -> Random (up to 15 plants)
     * 
     * Excludes plants the customer has already purchased.
     * 
     * @param customerId Customer identifier
     * @return Vector of up to 15 recommended plant pointers, unique and tailored to customer preferences
     */
    std::vector<Plant*> getPersonalizedRecommendations(const std::string& customerId);

    /**
     * @brief Get the number of commands currently in the action queue
     * @return Queue size (pending commands)
     */
    int getQueueSize();

    /**
     * @brief Get the number of undoable restock operations in history
     * @return Size of restock undo history
     */
    int getRestockHistorySize();

    /**
     * @brief Execute the next command in the queue
     * @return True if a command was processed, false if queue is empty or execution failed
     */
    bool processNextCommand();

    /**
     * @brief Execute all commands in the queue
     * @return Number of commands successfully processed
     */
    int processAllCommands();

    /**
     * @brief Undo the most recent restock operation
     * @return True if undo succeeded, false if no restock history exists
     */
    bool undoLastRestock();

    /**
     * @brief Enqueue a water command for deferred execution
     * @param plants Vector of plants to water
     * @param userId Identifier of the user issuing the command 
     */
    void enqueueWater(std::vector<Plant*>& plants, const std::string& userId);

    /**
     * @brief Enqueue a fertilize command for deferred execution
     * @param plants Vector of plants to fertilize
     * @param userId Identifier of the user issuing the command 
     */
    void enqueueFertilize(std::vector<Plant*>& plants, const std::string& userId);

    /**
     * @brief Enqueue a spray insecticide command for deferred execution
     * @param plants Vector of plants to spray
     * @param userId Identifier of the user issuing the command 
     */
    void enqueueSpray(std::vector<Plant*>& plants, const std::string& userId);

    /**
     * @brief Enqueue a restock command (undoable) for deferred execution
     * @param sku Species SKU to restock
     * @param qty Quantity to add
     * @param userId Identifier of the user issuing the command
     */
    void enqueueRestock(const std::string& sku, int qty, const std::string& userId);
    
private:

    /// Inventory subsystem: tracks stock levels and plant availability
    InventoryService* inv = nullptr;
    /// Sales subsystem: orders, receipts, and transactions
    SalesService* sales = nullptr;
    /// Staff subsystem: staff registry and task/assignment management
    StaffService* staff = nullptr;
    /// Greenhouse core: plant container, lifecycle ticking, and observer notifications
    Greenhouse* greenhouse = nullptr;
    /// Species metadata: shared flyweights with care/biome details
    SpeciesCatalog* catalog = nullptr;
    /// Prototype registry: factories/prototypes for creating plants by SKU
    PlantRegistry* protos = nullptr;
    /// Customer subsystem: customer registry and history
    CustomerService* customerService = nullptr;
    /// Command invoker: queues, executes, and undoes commands (e.g., restock)
    ActionLog* invoker = nullptr;
};
#endif