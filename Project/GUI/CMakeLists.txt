cmake_minimum_required(VERSION 3.21)
project(NurseryGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Adjust if needed (Qt install path)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.3/mingw_64")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# === GUI sources ===
set(GUI_SOURCES
    src/main.cpp
    src/SimpleLoginDialog.h
    src/SimpleLoginDialog.cpp
    src/SimpleCustomerWindow.h
    src/SimpleCustomerWindow.cpp
    src/SimpleStaffWindow.h
    src/SimpleStaffWindow.cpp
)

# === Backend sources ===
set(BACKEND_SOURCES
    ${CMAKE_SOURCE_DIR}/Greenhouse.cpp
    ${CMAKE_SOURCE_DIR}/InventoryService.cpp
    ${CMAKE_SOURCE_DIR}/ServiceSubject.cpp
    ${CMAKE_SOURCE_DIR}/SpeciesCatalog.cpp
    ${CMAKE_SOURCE_DIR}/Plant.cpp
    ${CMAKE_SOURCE_DIR}/PlantRegistry.cpp
    ${CMAKE_SOURCE_DIR}/MatureState.cpp
    ${CMAKE_SOURCE_DIR}/GrowingState.cpp
    ${CMAKE_SOURCE_DIR}/WiltingState.cpp
    ${CMAKE_SOURCE_DIR}/DeadState.cpp
    ${CMAKE_SOURCE_DIR}/SeedlingState.cpp
    ${CMAKE_SOURCE_DIR}/PlantKitFactory.cpp
    ${CMAKE_SOURCE_DIR}/TropicalFactory.cpp
    ${CMAKE_SOURCE_DIR}/DesertFactory.cpp
    ${CMAKE_SOURCE_DIR}/MediterraneanFactory.cpp
    ${CMAKE_SOURCE_DIR}/IndoorFactory.cpp
    ${CMAKE_SOURCE_DIR}/WetlandFactory.cpp
    ${CMAKE_SOURCE_DIR}/Water.cpp
    ${CMAKE_SOURCE_DIR}/Restock.cpp
    ${CMAKE_SOURCE_DIR}/Fertilize.cpp
    ${CMAKE_SOURCE_DIR}/Spray.cpp
    ${CMAKE_SOURCE_DIR}/Command.cpp
    ${CMAKE_SOURCE_DIR}/ActionLog.cpp
    ${CMAKE_SOURCE_DIR}/MacroCommand.cpp
    ${CMAKE_SOURCE_DIR}/StaffService.cpp
    ${CMAKE_SOURCE_DIR}/SalesService.cpp
    ${CMAKE_SOURCE_DIR}/NurseryFacade.cpp
    ${CMAKE_SOURCE_DIR}/TropicalStrategy.cpp
    ${CMAKE_SOURCE_DIR}/DesertStrategy.cpp
    ${CMAKE_SOURCE_DIR}/MediterraneanStrategy.cpp
    ${CMAKE_SOURCE_DIR}/IndoorStrategy.cpp
    ${CMAKE_SOURCE_DIR}/WetlandStrategy.cpp
    ${CMAKE_SOURCE_DIR}/SpeciesFlyweight.cpp
    ${CMAKE_SOURCE_DIR}/CustomerService.cpp
    ${CMAKE_SOURCE_DIR}/PlantItem.cpp
    ${CMAKE_SOURCE_DIR}/ReinforcedPot.cpp
    ${CMAKE_SOURCE_DIR}/MessageCard.cpp
    ${CMAKE_SOURCE_DIR}/GiftWrap.cpp
    ${CMAKE_SOURCE_DIR}/ChatMediator.cpp
    ${CMAKE_SOURCE_DIR}/Customer.cpp
    ${CMAKE_SOURCE_DIR}/Staff.cpp
    ${CMAKE_SOURCE_DIR}/GreenhouseIterator.cpp
    ${CMAKE_SOURCE_DIR}/SkuIterator.cpp
    ${CMAKE_SOURCE_DIR}/StateIterator.cpp
    ${CMAKE_SOURCE_DIR}/SoilMix.cpp
    ${CMAKE_SOURCE_DIR}/AquaticSoilMix.cpp
    ${CMAKE_SOURCE_DIR}/GrittyLimeSoilMix.cpp
    ${CMAKE_SOURCE_DIR}/LightAirySoilMix.cpp
    ${CMAKE_SOURCE_DIR}/PeatSoilMix.cpp
    ${CMAKE_SOURCE_DIR}/SandySoilMix.cpp
    ${CMAKE_SOURCE_DIR}/Pot.cpp
    ${CMAKE_SOURCE_DIR}/TerracottaPot.cpp
    ${CMAKE_SOURCE_DIR}/GlazedCeramicPot.cpp
    ${CMAKE_SOURCE_DIR}/CeramicPot.cpp
    ${CMAKE_SOURCE_DIR}/UnglazedClayPot.cpp
    ${CMAKE_SOURCE_DIR}/AquaticBasketPot.cpp
)

# === Build target ===
qt_add_executable(${PROJECT_NAME}
    ${GUI_SOURCES}
    ${BACKEND_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

# === Include directories (so headers from root are found) ===
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# === Windows executable option ===
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE FALSE)
endif()

# === Output location ===
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
