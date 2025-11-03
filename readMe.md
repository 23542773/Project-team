# Compilation Prerequisites
Qt
C++
CMake
Make utility

# Build Instructions(cmake)

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
make

# The executable will be in build/bin/NurseryGUI

# From the build directory after CMake build
./bin/NurseryGUI

# Plant Nursery Simulator
A plant nursery management system that simulates plant lifecycles, inventory management, staff coordination, and customer sales using 13 design patterns.

# Description
The application models a plant nursery with plant growth cycles(Seedling → Growing → Mature → Wilting → Dead). Different requirements for each plant type. Adding water pesticide etc. to ensure it stays alive(healtpoints>0). It handles everything from storing, growing and reproducing(prototype) plants in the greenhouse. Customer sales and customizable plants(decorator). Also staff task like sales, plant care and inventory staff. Inventory managment like stock levels(mature plants) check if stock available when customer try to aquire plant. Customers able to browse by plant type(Tropical Dessert,Mediterranean, Indoor, Wetland). Also able to send messages to sales staff. With real time dashboard updates in the GUI like seeing the plant lifecycle and being able to maintain its neccesary condition for it to survive. 

# Defualt Users(code in main.cpp)
# Staff Users:
STF1 Sales
STF2 PlantCare
STF3 Inventory
STF4 Sale
STF5 Sales
STF6 Inventory
STF7 PlantCare

# Customer Users:
CUST1 (John Doe)
CUST2 (Alice)
CUST3 (Bob Smith)
CUST4 (Emma Johnson)

# Data Files(main.cpp)
# Plant Species(25)
Tropical: Fern, Monstera, Palm, Bamboo, Orchid
Desert: Cactus, Aloe, Agave, Succulent, Yucca
Mediterranean: Rose, Lavender, Olive, Jasmine, Thyme
Indoor: Pothos, SnakePlant, SpiderPlant, PeaceLily, RubberPlant
Wetland: Lotus, WaterLily, Papyrus, Cattail, Iris

# Plants
25 Seedling
25 Growing
25 Mature

# Configuration
# Simulation
Changes over a n amount of seconds
Plant States: Seedling → Growing → Mature → Wilting → Dead
Biomes: Tropical, Desert, Mediterranean, Indoor, Wetland

# Design Patterns
# Creational (3)
Singleton (Plant states)
Prototype (Plant creation)
Factory Method (Biome components)

# Structural (3)
Facade (Simplified API)
Flyweight (Species data)
Decorator (Sale items)

# Behavioral (7)
Command (Actions & undo/redo)
Iterator (Collection traversal)
Mediator (Service communication)
Observer (Event notification)
State (Plant lifecycle)
Strategy (Biome care)
Template Method (Plant assembly)
