#ifndef PACKAGEDIRECTOR_H
#define PACKAGEDIRECTOR_H
#include "PackageBuilder.h"


class PackageDirector {
private:
PackageBuilder& b;

public: 
virtual void construct();

};
#endif // PACKAGEDIRECTOR_H