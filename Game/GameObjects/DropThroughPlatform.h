#ifndef DROP_THROUGH_PLATFORM_H
#define DROP_THROUGH_PLATFORM_H

//Class by Jake G. Cunningham

#include "Platform.h"
#include <iostream>

class DropThroughPlatform : public Platform {
public:
	//Constructors
	DropThroughPlatform(Model* model_, bool isGravity_);
	DropThroughPlatform(Model* model_, glm::vec3 position_, bool isGravity_);

};

#endif // !DROP_THROUGH_PLATFORM_H