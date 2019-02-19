#ifndef ENTITY_H
#define ENTITY_H

//Class by Jake G. Cunningham

#include "../../Engine/Rendering/3D/GameObject.h"

class Entity : public GameObject {
public:
	//Constructors
	Entity(Model* model_, glm::vec3 position_, bool isGravity_);
	~Entity();

	//Entity Specific methods
	virtual void Update(const float deltaTime_) = 0;

	//getters and setters
	void SetGravity(bool isGravity_);
	bool GetGravity();

	void SetHealth(bool health_);
	int GetHealth();

	void SetStamina(bool stamina_);
	int GetStamina();

	void SetSpeed(bool speed_);
	float GetSpeed();

	void setVelocity(glm::vec3 velocity_);
	glm::vec3 getVelocity();

	void setAcceleration(glm::vec3 accleration_);
	glm::vec3 getAcceleration();

private:
	//boolian to turn gravity on and off
	bool isGravity;

	//private variables that will belong to all entities
	int health;
	int stamina;
	float speed;

	//Physics variables
	glm::vec3 velocity;
	glm::vec3 acceleration;

};

#endif // !ENTITY_H