#ifndef PACKAGEDIRECTOR_H
#define PACKAGEDIRECTOR_H

class PackageDirector 
{
    public:
        /**
         * @brief Virtual destructor
         */
        virtual ~PackageDirector() = default;
        
        /**
         * @brief Construct a package
         */
        virtual void construct() = 0;
};

#endif // PACKAGEDIRECTOR_H