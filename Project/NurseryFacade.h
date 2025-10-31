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


class NurseryFacade 
{
public:

    NurseryFacade(InventoryService* inv, SalesService* sales, StaffService* staff, CustomerService* customers, Greenhouse* greenhouse,
    SpeciesCatalog* catalog, ActionLog* invoker);
    
    std::vector<Plant*> browseAvailable();

    struct Receipt checkout(std::string customerId, std::vector<events::OrderLine>& lines, double amountPaid);

    std::vector<struct Receipt> getCustomerReceipts(std::string customerId);

    Plant* getPlant(std::string id);

    std::vector<events::Order> getCustomerOrders(std::string customerId);

    std::vector<events::Order> getStaffOrders(std::string staffId);

    std::vector<Staff> listAllStaff();

    std::vector<Customer> listAllCustomers();

    std::vector<std::shared_ptr<PlantFlyweight>> listAllSpecies();


    int getSpeciesQuantity(std::string sku);

    std::vector<Plant*> listAllPlants();

    void waterPlants(std::vector<Plant*>& plants);

    void fertilizePlants(std::vector<Plant*>& plants);

    void sprayInsecticide(std::vector<Plant*>& plants);

    void tickAllPlants();

    // Routines
    void runMorningRoutine(std::vector<Plant*>& plants);  
    void runNightRoutine(std::vector<Plant*>& plants); 
    void runUrgentCare();  

    bool isValidCustomer(std::string id);

    bool isValidStaff(std::string id);
    

    bool completeOrder(std::string orderId);

    std::vector<struct Message> getConversation(const std::string& userA, const std::string& userB);

    Customer* getCustomer(std::string id);

    Staff* getStaff(std::string id);

    //Uses an algorithm to provide personalized plant recommendations based on customer's past orders.
    //If no order it uses seasonal plants plus randoms.
    //If customer has past orders, it analyzes purchased plant species and suggests similar plants.
    //Biome -> Season -> Similar Care Presets -> Random if they have order history
    std::vector<Plant*> getPersonalizedRecommendations(const std::string& customerId);

    int getQueueSize();

    int getRestockHistorySize();

    bool processNextCommand();

    int processAllCommands();

    bool undoLastRestock();

    void enqueueWater(std::vector<Plant*>& plants, const std::string& userId);

    void enqueueFertilize(std::vector<Plant*>& plants, const std::string& userId);

    void enqueueSpray(std::vector<Plant*>& plants, const std::string& userId);

    void enqueueRestock(const std::string& sku, int qty, const std::string& userId);
    
private:

    InventoryService* inv = nullptr;
    SalesService* sales = nullptr;
    StaffService* staff = nullptr;
    Greenhouse* greenhouse = nullptr;
    SpeciesCatalog* catalog = nullptr;
    PlantRegistry* protos = nullptr;
    CustomerService* customerService = nullptr;
    ActionLog* invoker = nullptr;
};
#endif