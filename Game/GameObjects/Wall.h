#ifndef WALL_H
#define WALL_H

//Class by Jake G. Cunningham

#include "Platform.h"
#include <iostream>

class Wall : public Platform {
public:
	//Constructors
	Wall(Model* model_, bool isGravity_);
	Wall(Model* model_, glm::vec3 position_, bool isGravity_);

};

#endif // !WALL_H