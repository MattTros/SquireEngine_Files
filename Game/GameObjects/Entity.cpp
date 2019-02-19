#include"Entity.h"

//The angle you must rotate by to get the brick obj to face the screen.
#define NINETY_DEGREES 1.575f

Entity::Entity(Model* model_, glm::vec3 position_, bool isGravity_) : GameObject(model_, position_) {
	//default things
	isGravity = isGravity_;
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
}

Entity::~Entity() {

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

void Entity::SetSpeed(bool speed_) {
	speed = speed_;
}

float Entity::GetSpeed() {
	return speed;
}

void Entity::setVelocity(glm::vec3 velocity_) {
	velocity = velocity_;
}

glm::vec3 Entity::getVelocity() {
	return velocity;
}

void Entity::setAcceleration(glm::vec3 accleration_) {
	acceleration = accleration_;
}

glm::vec3 Entity::getAcceleration() {
	return acceleration;
}