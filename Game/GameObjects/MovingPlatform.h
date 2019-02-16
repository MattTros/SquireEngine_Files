#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

//Class by Jake G. Cunningham#pragma once
#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "Platform.h"

class MovingPlatform : public Platform {
public:
	//Constructors
	MovingPlatform(Model* model_, glm::vec3 startPos_, glm::vec3 endPos_, float speed_);
	~MovingPlatform();

	//Platform Specific methods
	void Update(const float deltaTime_);

private:

	void MoveTowards(GameObject* other_, const float deltaTime_);

	//movement variables
	float speed;
	glm::vec3 velocity;
	glm::vec3 position;

	//state to see which position the platform is moving towards
	int state;

	//Used for determining where the platformis moving
	GameObject* moveTowards;
	GameObject* pos1;
	GameObject* pos2;
	Model* dice;
};

#endif // !MOVING_PLATFORM