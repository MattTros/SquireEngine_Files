#ifndef PLATFORM_H
#define PLATFORM_H

//Class by Jake G. Cunningham

#include "../../Engine/Rendering/3D/GameObject.h"
#include <iostream>

class Platform : public GameObject {
public:
	//Constructors
	Platform(Model* model_, bool isGravity_);
	Platform(Model* model_, glm::vec3 position_, bool isGravity_);
	~Platform();

	//Platform Specific methods
	void OnCollision(GameObject* other_);
	void Update(const float deltaTime_);

	//sword getter
	void SetVelocity(glm::vec3 velocity_);

	//boolian to turn gravity on and off
	bool isGravity;
private:
	
	//Physics variables
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 position;

};

#endif // !PLATFORM