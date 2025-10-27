#ifndef SPECIESCATALOG_H
#define SPECIESCATALOG_H

#include <string>
#include <vector>


class SpeciesCatalog 
{
    public:
        /**
         * @brief Virtual destructor
         */
        virtual ~SpeciesCatalog() = default;
        
        /**
         * @brief Check if SKU exists in catalog
         * @param sku SKU to check
         * @return true if SKU exists
         */
        virtual bool hasSKU(const std::string& sku) const = 0;
        
        /**
         * @brief Get all registered SKUs
         * @return Vector of all SKU strings
         */
        virtual std::vector<std::string> getAllSKUs() const = 0;
        
        /**
         * @brief Get species name for SKU
         * @param sku SKU identifier
         * @return Species name, or empty string if not found
         */
        virtual std::string getSpeciesName(const std::string& sku) const = 0;
        
        /**
         * @brief Get environment type for SKU
         * @param sku SKU identifier
         * @return Environment type, or empty string if not found
         */
        virtual std::string getEnvironmentType(const std::string& sku) const = 0;
};

#endif // SPECIESCATALOG_H