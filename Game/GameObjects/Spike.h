#ifndef SPIKE_H
#define SPIKE_H

//Class by Jake G. Cunningham

#include "Platform.h"
#include <iostream>

class Spike : public Platform {
public:
	//Constructors
	Spike(Model* model_, bool isGravity_);
	Spike(Model* model_, glm::vec3 position_, bool isGravity_);

};

#endif // !SPIKE_H