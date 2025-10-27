#ifndef DUMMY_SPECIESCATALOG_H
#define DUMMY_SPECIESCATALOG_H

#include "SpeciesCatalog.h"
#include <map>
#include <string>
#include <vector>

/**
 * @file dummy/DummySpeciesCatalog.h
 * @brief Standalone dummy SpeciesCatalog for testing
 * @author Damian moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real SpeciesCatalog implementation
 */

class DummyPlantFlyweight;

/**
 * @class DummySpeciesCatalog
 * @brief Standalone dummy catalog - NO INHERITANCE
 * 
 * We will change this later.
 */
class DummySpeciesCatalog:public SpeciesCatalog {
private:
    std::map<std::string, DummyPlantFlyweight*> speciesPool;

public:
    /**
     * @brief Constructor - automatically populates with dummy species
     * 
     * Initializes catalog with:
     * - SUCC-001: Aloe Vera (Indoor)
     * - CACT-001: Desert Rose (Desert)
     * - ORCH-001: Orchid (Tropical)
     * - HERB-023: Lavender (Mediterranean)
     * - FERN-005: Boston Fern (Wetland)
     */
    DummySpeciesCatalog();

    ~DummySpeciesCatalog();

    /**
     * @brief Get species by SKU
     * @param sku SKU identifier
     * @return Pointer to DummyPlantFlyweight, or nullptr if not found
     */
    DummyPlantFlyweight* getBySKU(const std::string& sku) const;

    /**
     * @brief Register a new species
     * @param sku SKU identifier
     * @param species DummyPlantFlyweight to register
     */
    void registerSpecies(const std::string& sku, DummyPlantFlyweight* species);

    /**
     * @brief Check if SKU exists in catalog
     * @param sku SKU to check
     * @return true if SKU exists
     */
    bool hasSKU(const std::string& sku) const;

    /**
     * @brief Get all registered SKUs
     * @return Vector of all SKU strings
     */
    std::vector<std::string> getAllSKUs() const;

    /**
     * @brief Get species name for SKU
     * @param sku SKU identifier
     * @return Species name, or empty string if not found
     */
    std::string getSpeciesName(const std::string& sku) const;

    /**
     * @brief Get environment type for SKU
     * @param sku SKU identifier
     * @return Environment type, or empty string if not found
     */
    std::string getEnvironmentType(const std::string& sku) const;
};

#endif // DUMMY_SPECIESCATALOG_H