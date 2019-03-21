#ifndef FLY_H
#define FLY_H

//Class by Jake G. Cunningham
#include "Enemy.h"
#include "../../Engine/Graphics/ParticleSystem.h"

class Fly : public Enemy {
public:
	Fly(Model* model_, glm::vec3 position_, Entity* player_);
	~Fly();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void CollisionResponse(GameObject* other_, const float deltaTime_);
	GameObject* GetGas();

private:
	//private methods
	void Patrol(const float deltaTime_);
	void Chase(const float deltaTime_);
	void Attack();
	void Knockback(const float deltaTime_);

	//player object that gets passed into the constructor
	Entity* player;

	//temp physics variable
	glm::vec3 position;
	glm::vec3 acceleration;
	glm::vec3 velocity;

	//State variables
	int state;

	//Particle Variables
	Model* particle;
	ParticleSystem* fountain;

	//Angle for sin wave movement
	int angle;

	//attack variables
	GameObject* attackBox;
	Model* attackModel;
	float attackTimer;
	bool isAttacking;
	bool knockedBack;
	int knockbackDirection;
	glm::vec3 gasPos;

};

#endif // !FLY_H
