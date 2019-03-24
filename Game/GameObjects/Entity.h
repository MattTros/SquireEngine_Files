#ifndef ENTITY_H
#define ENTITY_H

//Class by Jake G. Cunningham

#include "../../Engine/Rendering/3D/GameObject.h"
#include "../../Engine/Events/KeyboardInputManager.h"
#include "../../Engine/Core/Timer.h"

//struct Rigidbody
//{
//	float gravityScale;
//	float mass;
//	float friction;
//	glm::vec3 velocity;
//	Entity* entity;
//
//	inline Rigidbody() 
//	{
//		entity = nullptr;
//		gravityScale = 1.0f;
//		mass = 1.0f;
//		friction = 0.0f;
//		velocity = glm::vec3(0.0f);
//	}
//
//	inline Rigidbody(Entity* entity_)
//	{
//		entity = entity_; 
//		gravityScale = 1.0f;
//		mass = 1.0f;
//		friction = 0.0f;
//		velocity = glm::vec3(0.0f);
//	}
//
//	inline void AddForce(glm::vec3 force_)
//	{
//		velocity += force_ * mass;
//	}
//};

class Entity : public GameObject {
public:
	//Constructors
	Entity(Model* model_, glm::vec3 position_, bool isGravity_);
	~Entity();

	//Entity Specific methods
	void Update(const float deltaTime_);

	//Reseting gravity
	void ResetGravity(GameObject* currentPlatform_);

	//Default collision method, will not be complete for enemies or players, but will streamline that process
	void DefaultCollision(GameObject* other_, const float deltaTime_);

	//getters and setters
	void SetGravity(bool isGravity_);
	bool GetGravity();

	void SetHealth(int health_);
	int GetHealth();

	void SetStamina(int stamina_);
	int GetStamina();

	void SetSpeed(float speed_);
	float GetSpeed();

	void SetVelocity(glm::vec3 velocity_);
	glm::vec3 GetVelocity();

	void SetAcceleration(glm::vec3 accleration_);
	glm::vec3 GetAcceleration();

	void SetCurrentPlatform(GameObject* currentPlatform_);

private:
	//boolean to turn gravity on and off
	bool isGravity;

	WaitForSeconds* spikeWFS;
	WaitForSeconds dropThroughTimer;

	//private variables that will belong to all entities
	int health;
	int stamina;
	float speed;

	//Physics variables
	glm::vec3 velocity;
	glm::vec3 acceleration;

	//platform variable for turning gravity back on
	GameObject* currentPlatform;
};

#endif // !ENTITY_H