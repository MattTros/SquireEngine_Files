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
	SetTag("Platform");
	currentPlatform = nullptr;
	//! Drop Through WFS:
	dropThroughTimer = WaitForSeconds();
	dropThroughTimer.active = false;
	dropThroughTimer.waitTime = 1.0f;
	dropThroughTimer.seconds = 0.0f;
}

Entity::~Entity() {

}

//Entity Specific methods
void Entity::Update(const float deltaTime_) {
	if (currentPlatform != nullptr) {
		ResetGravity(currentPlatform);
	}

	if (dropThroughTimer.active)
	{
		if (dropThroughTimer.seconds >= dropThroughTimer.waitTime)
		{
			dropThroughTimer.active = false;
			dropThroughTimer.seconds = 0.0f;
		}
		dropThroughTimer.seconds += deltaTime_;
	}
}

//Reseting gravity
void Entity::ResetGravity(GameObject* currentPlatform_) {
	//If gravity then don't bother calculating
	if (isGravity) {
		return;
	}
	glm::vec3 distance = abs(GetPosition() - currentPlatform_->GetPosition());
	//length of the platform
	glm::vec3 platLength = abs(currentPlatform_->GetBoundingBox().minVert - currentPlatform_->GetBoundingBox().maxVert);

	//length of the this object
	glm::vec3 thisLength = abs(GetBoundingBox().minVert - GetBoundingBox().maxVert);

	//if you move off the platform apply gravity
	if (distance.x >= ((platLength.x + (thisLength.x)) / 2.0f)) {
		SetGravity(true);
		currentPlatform = nullptr;
	}
}

void Entity::DefaultCollision(GameObject* other_, const float deltaTime_) {
	//check if there is any bounding box intersection
	if (other_->GetBoundingBox().Intersects(&GetBoundingBox())) {
		//determine which object is being collided with
		if (other_->GetTag() == "Platform") {
			//Collision with specific object response

			if (GetTag() == "Enemy") {
				isGravity = false;
			}

			//distance needs to be positive
			glm::vec3 distance = GetPosition() - other_->GetPosition();
			//length of the platform
			glm::vec3 platLength = abs(other_->GetBoundingBox().minVert - other_->GetBoundingBox().maxVert);
			//length of this object
			glm::vec3 thisLength = abs(GetBoundingBox().minVert - GetBoundingBox().maxVert);

			if (distance.y >= ((platLength.y + (thisLength.y / 2)) / 2.0f)) {
				//the player is on the side of the platform
				//if the entity is on top
				isGravity = false;
				currentPlatform = other_;
				glm::vec3 vel = glm::vec3(GetVelocity().x, 0.0f, GetVelocity().z);
				SetVelocity(vel);

			}
			
		}

		if (other_->GetTag() == "DropThroughPlatform")
		{
			//Collision with specific object response

			if (GetTag() == "Enemy") 
			{
				isGravity = false;
			}


			if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_S) && GetTag() == "Player")
			{
				dropThroughTimer.active = true;
				SetGravity(true);
			}

			if (!dropThroughTimer.active)
			{
				//distance needs to be positive
				glm::vec3 distance = GetPosition() - other_->GetPosition();
				//length of the platform
				glm::vec3 platLength = abs(other_->GetBoundingBox().minVert - other_->GetBoundingBox().maxVert);
				//length of this object
				glm::vec3 thisLength = abs(GetBoundingBox().minVert - GetBoundingBox().maxVert);

				if (distance.y >= ((platLength.y + (thisLength.y / 2)) / 2.0f))
				{
					//the player is on the side of the platform
					//if the entity is on top
					isGravity = false;
					currentPlatform = other_;
					glm::vec3 vel = glm::vec3(GetVelocity().x, 0.0f, GetVelocity().z);
					SetVelocity(vel);

				}
			}
		}

		if (other_->GetTag() == "MovingPlatform") {
			//Collision with specific object respone
			//TODO

			currentPlatform = other_;
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

void Entity::SetHealth(int health_) {
	health = health_;
}

int Entity::GetHealth() {
	return health;
}

void Entity::SetStamina(int stamina_) {
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

void Entity::SetCurrentPlatform(GameObject* currentPlatform_) {
	currentPlatform = currentPlatform_;
}
