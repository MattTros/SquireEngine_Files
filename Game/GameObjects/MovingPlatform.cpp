#include "MovingPlatform.h"

//take in model for the platform, two positions for the pos game objects (the points the platform will move between), and a speed for how fast the platform will move.
MovingPlatform::MovingPlatform(Model* model_, glm::vec3 startPos_, glm::vec3 endPos_, float speed_) : Platform(model_, startPos_, false) {
	speed = speed_;

	dice = new Model("Dice.obj", "Dice.mtl", BASE_SHADER);

	pos1 = new GameObject(dice, startPos_);
	pos2 = new GameObject(dice, endPos_);

	pos1->SetScale(glm::vec3(0.0));
	pos2->SetScale(glm::vec3(0.0));

	state = 0;
}

MovingPlatform::~MovingPlatform() {
	delete pos1;
	delete pos2;
	delete dice;
}

void MovingPlatform::Update(const float deltaTime_) {
	//check what state the platform is in and move to the correct platform
	if (state == 0) {
		moveTowards = pos2;
	}
	else {
		moveTowards = pos1;
	}
	MoveTowards(moveTowards, deltaTime_);
}

void MovingPlatform::MoveTowards(GameObject* other_, const float deltaTime_) {
	//Get position
	position = GetPosition();
	//direction = the normalized distance between the other object and the platform
	glm::vec3 direction = glm::normalize(other_->GetPosition() - position);
	//velocity equation
	velocity = speed * direction;
	//new position equation applying velocity
	position += velocity * deltaTime_;

	SetPosition(position);
	//check the distance to set the state if the platform is close to it's final position
	float distance = glm::length(other_->GetPosition() - position);
	if (distance <= 0.5f) {
		if (state == 0) {
			state = 1;
		}
		else {
			state = 0;
		}
	}
}