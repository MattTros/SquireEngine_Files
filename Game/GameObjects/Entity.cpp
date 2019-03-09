#include"Entity.h"

//The angle you must rotate by to get the brick obj to face the screen.
#define NINETY_DEGREES 1.575f

Entity::Entity(Model* model_, glm::vec3 position_, bool isGravity_) : GameObject(model_, position_) {
	//default things
	isGravity = isGravity_;
	spikeWFS = new WaitForSeconds();
	spikeWFS->active = false;
	health = 0;
	stamina = 0;
	speed = 0;
	velocity = glm::vec3(0);
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	//properly rotate the brick obj
	SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	SetAngle(NINETY_DEGREES);
	//set the tag of this object
	SetTag("");
	position;
}

Entity::~Entity() {

}

void Entity::Update(const float deltaTime_) {
	if (GetGravity() == true) {
		velocity += (velocity * deltaTime_) + (0.5f * acceleration * (deltaTime_ * deltaTime_));
		position += velocity * deltaTime_;
		SetPosition(position);
	}
}

void Entity::DefaultCollision(GameObject* other_, const float deltaTime_) {
	//check if there is any bounding box intersection
	if (other_->GetBoundingBox().Intersects(&GetBoundingBox())) {
		//determine which object is being collided with
		if (other_->GetTag() == "Platform") {
			//Collision with specific object respone
			isGravity = false;
		}

		if (other_->GetTag() == "MovingPlatform") {
			//Collision with specific object respone
			//TODO
		}

		if (other_->GetTag() == "Spike") {
			//deal 10 damage, wait 2 seconds, and deal 10 damage again
			if (!spikeWFS->active) {
				health -= 10;
				spikeWFS->active = true;
			}
			spikeWFS->waitTime = 2.0f;
			spikeWFS->seconds += deltaTime_;
			if (spikeWFS->seconds > spikeWFS->waitTime) {
				spikeWFS->seconds = 0.0f;
			}
		}
	}
}

void Entity::SetGravity(bool isGravity_) {
	isGravity = isGravity_;
}

bool Entity::GetGravity() {
	return isGravity;
}

void Entity::SetHealth(bool health_) {
	health = health_;
}

int Entity::GetHealth() {
	return health;
}

void Entity::SetStamina(bool stamina_) {
	stamina = stamina_;
}

int Entity::GetStamina() {
	return stamina;
}

void Entity::SetSpeed(float speed_) {
	speed = speed_;
}

float Entity::GetSpeed() {
	return speed;
}

void Entity::SetVelocity(glm::vec3 velocity_) {
	velocity = velocity_;
}

glm::vec3 Entity::GetVelocity() {
	return velocity;
}

void Entity::SetAcceleration(glm::vec3 accleration_) {
	acceleration = accleration_;
}

glm::vec3 Entity::GetAcceleration() {
	return acceleration;
}
