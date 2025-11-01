/**
 * @file test_observer_unit.cpp
 * @brief Unit tests for Observer pattern (NurseryObserver / ServiceSubject)
 * @date 2025-11-01
 *
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_COLORS_NONE

#include "doctest.h"

#include "../ServiceSubject.h"
#include "../NurseryObserver.h"
#include "../Events.h"
#include "../StaffDash.h"
#include "../CustomerDash.h"

#include <string>
#include <vector>

// Small helper: TestSubject exposes protected notify methods as public
class TestSubject : public ServiceSubject 
{
    public:
    void notifyPlant(const events::Plant& p) { notify(p); }
    void notifyStock(const events::Stock& s) { notify(s); }
    void notifyOrder(events::Order& o) { notify(o); }
};

TEST_CASE("Observer Unit: registration and basic plant notifications") 
{
    TestSubject subject;
    StaffDash staff;
    CustomerDash customer;

    // No observers registered -> notifications should be no-ops / not crash
    events::Plant p0{ "P0", "SKU0", events::PlantType::Matured };
    subject.notifyPlant(p0);

    // Register both observers
    subject.addObserver(&staff);
    subject.addObserver(&customer);

    SUBCASE("Matured plant: customer receives matured ID; staff gets alert") 
    {
        // Reset internal state without reassigning 
        staff.clear();
        customer.clear();

        events::Plant matured{ "PLANT-UNIT-1", "ROSE001", events::PlantType::Matured };
        subject.notifyPlant(matured);

        // CustomerDash should record matured plant id
        const auto &mList = customer.getMatured();
        CHECK(mList.size() == 1);
        CHECK(mList[0] == "PLANT-UNIT-1");

        // StaffDash should have a matured alert
        const auto &alerts = staff.getAlerts();
        bool found = false;
        for (const auto &a : alerts) {
            if (a.find("Plant matured: PLANT-UNIT-1") != std::string::npos) { found = true; break; }
        }
        CHECK(found == true);
    }

    SUBCASE("Wilted plant: staff alerted; customer ignores") 
    {
        // Reset internal state without reassigning
        staff.clear();
        customer.clear();

        events::Plant wilted{ "PLANT-UNIT-2", "CACT001", events::PlantType::Wilted };
        subject.notifyPlant(wilted);

        // CustomerDash should not record wilted events
        CHECK(customer.getMatured().empty());

        // StaffDash should have a wilted alert
        const auto &alerts = staff.getAlerts();
        bool found = false;
        for (const auto &a : alerts) {
            if (a.find("Plant wilted: PLANT-UNIT-2") != std::string::npos) { found = true; break; }
        }
        CHECK(found == true);
    }
}

TEST_CASE("Observer Unit: stock and order events") 
{
    TestSubject subject;
    StaffDash staff;
    CustomerDash customer;

    subject.addObserver(&staff);
    subject.addObserver(&customer);

    // Reset state
    staff.clear();
    customer.clear();

    SUBCASE("Stock Low event should alert staff only") 
    {
        events::Stock s{ "SKU-LOW-1", events::StockType::Low };
        subject.notifyStock(s);

        const auto &alerts = staff.getAlerts();
        CHECK(!alerts.empty());//if we get any alerts
        bool sku_found = false;
        for (const auto &a : alerts) {
            if (a.find("SKU-LOW-1") != std::string::npos) { sku_found = true; break; }
        }
        CHECK(sku_found == true);

        // customer unaffected
        CHECK(customer.getMatured().empty());
    }

    SUBCASE("Order Created event should alert staff (new order)") 
    {
        events::Order o;
        o.orderId = "ORD-UNIT-1";
        o.customerId = "CUST-UNIT-1";
        o.type = events::OrderType::Created;

        subject.notifyOrder(o);

        const auto &alerts = staff.getAlerts();
        bool found = false;
        for (const auto &a : alerts) {
            if (a.find("New order: ORD-UNIT-1") != std::string::npos) { found = true; break; }
        }
        CHECK(found == true);
    }
}

TEST_CASE("Observer Unit: multiple observers and null-pointer robustness") 
{
    TestSubject subject;

    StaffDash staff1;
    StaffDash staff2;
    CustomerDash customer;

    staff1.clear();
    staff2.clear();
    customer.clear();

    subject.addObserver(&staff1);
    subject.addObserver(nullptr);
    subject.addObserver(&staff2);
    subject.addObserver(&customer);

    events::Plant matured{ "PLANT-UNIT-3", "SKU-X", events::PlantType::Matured };
    subject.notifyPlant(matured);

    // Both staff dashboards should have smae alerts
    const auto &a1 = staff1.getAlerts();
    const auto &a2 = staff2.getAlerts();
    CHECK(!a1.empty());
    CHECK(!a2.empty());
    CHECK(a1[0] == a2[0]);

    // Customer should have matured id
    const auto &mList = customer.getMatured();
    CHECK(mList.size() == 1);
    CHECK(mList[0] == "PLANT-UNIT-3");
}