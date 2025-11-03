#include <QApplication>
#include "SimpleLoginDialog.h"
#include "SimpleCustomerWindow.h"
#include "SimpleStaffWindow.h"
#include "../NurseryFacade.h"
#include "../Greenhouse.h"
#include "../SpeciesCatalog.h"
#include "../PlantRegistry.h"
#include "../InventoryService.h"
#include "../SalesService.h"
#include "../StaffService.h"
#include "../SeedlingState.h"
#include "../GrowingState.h"
#include "../MatureState.h"
#include "../TropicalFactory.h"
#include "../CustomerService.h"
#include "../DesertFactory.h"
#include "../MediterraneanFactory.h"
#include "../IndoorFactory.h"
#include "../WetlandFactory.h"
#include "../SpeciesFlyweight.h"
#include "../ChatMediator.h"
#include "../ActionLog.h"
#include "../CustomerDash.h"
#include "../StaffDash.h"
#include <QTimer>


int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    
    SpeciesCatalog catalog;
    PlantRegistry protos;
    Greenhouse greenhouse(&protos);
    Inventory store;
    InventoryService inv(store, greenhouse);
    
    CustomerDash customerDash;
    StaffDash staffDash;
    
    greenhouse.addObserver(&inv);       
    greenhouse.addObserver(&customerDash);
    greenhouse.addObserver(&staffDash);   
    
    SalesService sales;
    sales.addObserver(&staffDash);        
    
    ActionLog invoker;
    
    StaffService staff(nullptr);  
    CustomerService customers(nullptr);
    ChatMediator messenger;
    
    staff.setMediator(&messenger);
    customers.setMediator(&messenger);
    
    staff.addStaff("STF1", "Ethan", StaffRole::Sales);
    staff.addStaff("STF2", "Liam", StaffRole::PlantCare);
    staff.addStaff("STF3", "Sophia", StaffRole::Inventory);
    staff.addStaff("STF4", "Maria", StaffRole::Sales);
    staff.addStaff("STF5", "Olivia", StaffRole::Sales);
    staff.addStaff("STF6", "Noah", StaffRole::Inventory);
    staff.addStaff("STF7", "Ava", StaffRole::PlantCare);
    
    customers.addCustomer("CUST1", "John Doe");
    customers.addCustomer("CUST2", "Alice");
    customers.addCustomer("CUST3", "Bob Smith");
    customers.addCustomer("CUST4", "Emma Johnson");
    
    TropicalFactory tropical;
    DesertFactory desert;
    MediterraneanFactory med;
    IndoorFactory indoor;
    WetlandFactory wetland;

    std::vector<std::tuple<std::string, std::string, std::string, int,
    double, double, double, Season>> species = 
    {
    // Tropical (5 species)
    {"FERN","Fern","Tropical",6, 1.1,1.2,0.9,Season::Spring},
    {"MONST","Monstera","Tropical",9, 1.2,1.3,0.8,Season::Summer},
    {"PALM","Palm","Tropical",11, 1.0,1.1,0.9,Season::Summer},
    {"BAMBOO","Bamboo","Tropical",8, 1.1,1.0,0.9,Season::Spring},
    {"ORCHID","Orchid","Tropical",7, 1.3,1.2,0.8,Season::Autumn},

    // Desert (5 species)
    {"CACTUS","Cactus","Desert",12, 0.6,1.0,1.1,Season::Summer},
    {"ALOE","Aloe","Desert",7, 0.7,1.0,1.0,Season::Summer},
    {"AGAVE","Agave","Desert",10, 0.8,1.1,1.0,Season::Summer},
    {"SUCCUL","Succulent","Desert",6, 0.7,0.9,1.1,Season::Spring},
    {"YUCCA","Yucca","Desert",9, 0.6,1.0,1.0,Season::Autumn},

    // Mediterranean (5 species)
    {"ROSE","Rose","Mediterranean",10, 1.0,0.9,1.0,Season::Spring},
    {"LAV","Lavender","Mediterranean",8, 0.9,0.8,1.0,Season::Summer},
    {"OLIVE","Olive","Mediterranean",15, 0.8,0.8,1.1,Season::Autumn},
    {"JASMIN","Jasmine","Mediterranean",9, 1.0,0.9,1.0,Season::Spring},
    {"THYME","Thyme","Mediterranean",7, 0.9,0.8,1.1,Season::Summer},

    // Indoor (5 species)
    {"POTHOS","Pothos","Indoor",5, 1.0,1.0,1.0,Season::Autumn},
    {"SNAKE","SnakePlant","Indoor",6, 0.9,1.2,1.2,Season::Winter},
    {"SPIDER","SpiderPlant","Indoor",5, 1.1,1.0,1.0,Season::Spring},
    {"PEACE","PeaceLily","Indoor",7, 1.1,1.1,0.9,Season::Summer},
    {"RUBBER","RubberPlant","Indoor",8, 1.0,1.1,1.0,Season::Autumn},

    // Wetland (5 species)
    {"LOTUS","Lotus","Wetland",14, 1.3,1.1,0.8,Season::Summer},
    {"WATERL","WaterLily","Wetland",13, 1.2,1.0,0.8,Season::Summer},
    {"PAPYR","Papyrus","Wetland",12, 1.4,1.2,0.9,Season::Autumn},
    {"CATTAIL","Cattail","Wetland",10, 1.3,1.1,0.9,Season::Spring},
    {"IRIS","Iris","Wetland",11, 1.2,1.0,0.8,Season::Summer}
    };

    for (const auto& s : species)
    {
        auto fw = std::make_shared<SpeciesFlyweight>(
            std::get<0>(s), std::get<1>(s), std::get<2>(s), std::get<3>(s), std::get<4>(s),
            std::get<5>(s), std::get<6>(s), std::get<7>(s));
        catalog.add(fw);

        Plant* proto = nullptr;
        const auto& biome = std::get<2>(s);
        if (biome == "Tropical") proto = tropical.createPlant(fw->getSku()+"#PROTO","Green",fw.get());
        else if (biome == "Desert") proto = desert.createPlant(fw->getSku()+"#PROTO","Green",fw.get());
        else if (biome == "Mediterranean") proto = med.createPlant(fw->getSku()+"#PROTO","Green",fw.get());
        else if (biome == "Indoor") proto = indoor.createPlant(fw->getSku()+"#PROTO","Green",fw.get());
        else if (biome == "Wetland") proto = wetland.createPlant(fw->getSku()+"#PROTO","Green",fw.get());
        if (proto) protos.registerSeedling(fw->getSku(), std::unique_ptr<Plant>(proto));
    }

    // Create plants: 25 seedlings, 25 growing, 25 mature (1 of each species per state)
    PlantState* seedling = &SeedlingState::getInstance();
    PlantState* growing = &GrowingState::getInstance();
    PlantState* mature = &MatureState::getInstance();
    
    std::vector<std::string> colors = {"Green", "Red", "Yellow", "Blue", "Purple"};
    int plantCounter = 1;
    
    // 25 Seedling plants (1 of each species)
    for (size_t i = 0; i < species.size(); ++i) 
    {
        std::string sku = std::get<0>(species[i]);
        std::string id = sku + "#S" + std::to_string(i+1);
        std::string colour = colors[i % colors.size()];

        Plant* clone = protos.clone(sku, id, colour);
        clone->setState(seedling);
        clone->addWater(50);
        greenhouse.addPlant(std::unique_ptr<Plant>(clone));
    }
    
    // 25 Growing plants (1 of each species)
    for (size_t i = 0; i < species.size(); ++i) 
    {
        std::string sku = std::get<0>(species[i]);
        std::string id = sku + "#G" + std::to_string(i+1);
        std::string colour = colors[(i + 1) % colors.size()];  

        Plant* clone = protos.clone(sku, id, colour);
        clone->setState(growing);
        clone->addWater(70);
        greenhouse.addPlant(std::unique_ptr<Plant>(clone));
    }
    
    // 25 Mature plants (1 of each species)
    for (size_t i = 0; i < species.size(); ++i) 
    {
        std::string sku = std::get<0>(species[i]);
        std::string id = sku + "#M" + std::to_string(i+1);
        std::string colour = colors[(i + 2) % colors.size()]; 

        Plant* clone = protos.clone(sku, id, colour);
        clone->setState(mature);
        clone->addWater(100);
        greenhouse.addPlant(std::unique_ptr<Plant>(clone));
        inv.addPlant(id, sku);  
    }

    NurseryFacade facade(&inv, &sales, &staff, &customers, &greenhouse, &catalog, &invoker);

    // Continuous lifecycle ticking: call facade.tickAllPlants() periodically.
    // This simulates time passing for all plants via state checkChange transitions.
    QTimer lifecycleTimer(&app);
    lifecycleTimer.setInterval(10000);
    QObject::connect(&lifecycleTimer, &QTimer::timeout, &app, [&facade]() {
        facade.tickAllPlants();
    });
    lifecycleTimer.start();

    bool running = true;
    while (running) 
    {
        SimpleLoginDialog login(&facade);
        if (login.exec() != QDialog::Accepted) 
        {
            return 0;
        }

        QString userId = login.getUserId();
        QString roleStr = login.getRole();

        QMainWindow* mainWin = nullptr;
        if (roleStr == "Customer") 
        {
            auto* customerWin = new SimpleCustomerWindow(&facade, userId, nullptr, &customerDash);
            mainWin = customerWin;
            
            QObject::connect(customerWin, &SimpleCustomerWindow::logoutRequested, &app, [&running]() 
            {
                running = true;
            });
        } 
        else 
        {
            auto* staffWin = new SimpleStaffWindow(&facade, userId, nullptr, &staffDash);
            mainWin = staffWin;
            
            QObject::connect(staffWin, &SimpleStaffWindow::logoutRequested, &app, [&running]() 
            {
                running = true;
            });
        }
        
        mainWin->resize(1100, 700);
        mainWin->show();
        
        running = false;
        app.exec();
        
        delete mainWin;
    }
    return 0;
}