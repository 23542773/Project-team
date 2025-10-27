#ifndef PLANTKITFACTORY_H
#define PLANTKITFACTORY_H

#include <string>


class PlantKitFactory 
{
    public:
        /**
         * @brief Virtual destructor
         */
        virtual ~PlantKitFactory() = default;
        
        /**
         * @brief Get factory environment type
         * @return Environment name (e.g., "Indoor", "Desert")
         */
        virtual std::string getEnvironmentType() const = 0;
};

#endif // PLANTKITFACTORY_H