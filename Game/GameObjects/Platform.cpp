#include "Platform.h"

//The angle you must rotate by to get the brick obj to face the screen.
#define NINETY_DEGREES 1.575f

Platform::Platform(Model* model_, bool isGravity_) : GameObject(model_){
	//default things
	isGravity = isGravity_;
	velocity = glm::vec3(0);
	position = glm::vec3(0);
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	//properly rotate the brick obj
	SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	SetAngle(NINETY_DEGREES);
	//set the tag of this object
	SetTag("Platform");
}

Platform::Platform(Model* model_, glm::vec3 position_, bool isGravity_) : GameObject( model_, position_) {
	//default things
	isGravity = isGravity_;
	velocity = glm::vec3(0);
	position = glm::vec3(0);
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	//properly rotate the brick obj
	SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	SetAngle(NINETY_DEGREES);
	//set the tag of this object
	SetTag("Platform");
}

Platform::~Platform(){

}

void Platform::Update(const float deltaTime_)
{
	//if gravity, apply it, else do nothing
	if (isGravity) {	
		velocity += (velocity * deltaTime_) + (0.5f * acceleration * (deltaTime_ * deltaTime_));
		position += velocity * deltaTime_;
		SetPosition(position);
	}
	else {

	}
}

void Platform::onCollision(GameObject* other_) {
	//Collision detection
	if (GetBoundingBox().Intersects(&other_->GetBoundingBox())) {
		//Collision response
		isGravity = false;
	}

}
