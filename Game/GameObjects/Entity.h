#ifndef ENTITY_H
#define ENTITY_H

//Class by Jake G. Cunningham

#include "../../Engine/Rendering/3D/GameObject.h"
#include "../../Engine/Events/KeyboardInputManager.h"
#include "../../Engine/Core/Timer.h"

class Entity : public GameObject {
public:
	//Constructors
	Entity(Model* model_, glm::vec3 position_, bool isGravity_);
	~Entity();

	//Entity Specific methods
	virtual void Update(const float deltaTime_) = 0;

	//Default collision method, will not be complete for enemies or players, but will streamline that process
	void DefaultCollision(GameObject* other_, const float deltaTime_);

	//getters and setters
	void SetGravity(bool isGravity_);
	bool GetGravity();

	void SetHealth(bool health_);
	int GetHealth();

	void SetStamina(bool stamina_);
	int GetStamina();

	void SetSpeed(bool speed_);
	float GetSpeed();

	void SetVelocity(glm::vec3 velocity_);
	glm::vec3 GetVelocity();

	void SetAcceleration(glm::vec3 accleration_);
	glm::vec3 GetAcceleration();

private:
	//boolean to turn gravity on and off
	bool isGravity;

	WaitForSeconds* spikeWFS;

	//private variables that will belong to all entities
	int health;
	int stamina;
	float speed;

	//Physics variables
	glm::vec3 velocity;
	glm::vec3 acceleration;

};

#endif // !ENTITY_H
