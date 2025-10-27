#ifndef DUMMY_PACKAGEDIRECTOR_H
#define DUMMY_PACKAGEDIRECTOR_H

/**
 * @file dummy/DummyPackageDirector.h
 * @brief Standalone dummy PackageDirector for testing
 * @author damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real PackageDirector implementation
 */

// Forward declarations
class DummyPackageBuilder;

/**
 * @class DummyPackageDirector
 * @brief Standalone dummy director - NO INHERITANCE
 * 
 * When real PackageDirector is ready, change this to inherit from PackageDirector.
 */
class DummyPackageDirector {
private:
    DummyPackageBuilder* builder;

public:
    /**
     * @brief Constructor
     * @param builder Builder to use for construction
     */
    DummyPackageDirector(DummyPackageBuilder* builder);

    /**
     * @brief Destructor
     */
    ~DummyPackageDirector();

    /**
     * @brief Set builder
     * @param newBuilder New builder to use
     */
    void setBuilder(DummyPackageBuilder* newBuilder);

    /**
     * @brief Construct a default package
     * Runs the standard construction steps
     */
    void construct();
};

#endif // DUMMY_PACKAGEDIRECTOR_H