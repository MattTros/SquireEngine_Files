#include "Spike.h"

Spike::Spike(Model* model_, bool isGravity_) : Platform(model_, isGravity_) {
	//set the tag of this object
	SetTag("Spike");
}

Spike::Spike(Model* model_, glm::vec3 position_, bool isGravity_) : Platform(model_, position_, isGravity_) {
	//set the tag of this object
	SetTag("Spike");
}