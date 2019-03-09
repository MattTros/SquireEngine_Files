#include "Wall.h"

//The angle you must rotate by to get the brick obj to face the screen.
#define NINETY_DEGREES 1.575f

Wall::Wall(Model* model_, bool isGravity_) : Platform(model_, isGravity_) {
	//set the tag of this object
	SetTag("Wall");
	//properly rotate the brick obj
	
	SetRotation(glm::vec3(1.0f, 1.0f, 0.0f));
	
}

Wall::Wall(Model* model_, glm::vec3 position_, bool isGravity_) : Platform(model_, position_, isGravity_) {
	//set the tag of this object
	SetTag("Wall");
	//properly rotate the brick obj
	SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
}