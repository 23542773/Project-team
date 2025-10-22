#ifndef SERVICECOLLEAGUE_H
#define SERVICECOLLEAGUE_H
#include "Hub.h"
class ServiceColleague 
{

protected:

	Hub* hub;

public:

	/// \brief Sets Hub
	void setHub(Hub* h);
	virtual ~ServiceColleague() = 0;
};

#endif
