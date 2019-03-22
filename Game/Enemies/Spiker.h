#ifndef SPIKER_H
#define SPIKER_H

//Class by Jake G. Cunningham

#include "Enemy.h"

class Spiker : public Enemy {

public:
	Spiker(Model* model_, glm::vec3 position_, Entity* player_);
	~Spiker();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void CollisionResponse(GameObject* other_, const float deltaTime_);

private:
	//private methods
	void Patrol(const float deltaTime_);
	//Avoid the player
	void Chase(const float deltaTime_);

	void Attack();

	//player object that gets passed into the constructor
	Entity* player;

	//temp physics variable
	glm::vec3 position;
	glm::vec3 acceleration;
	glm::vec3 velocity;

	//variable to decide what state the enemy is in
	int state;
	bool patrolRight;

	//iframe stuff
	WaitForSeconds wfs;
	float attackTimer;

	//attack variables
	GameObject* projectile;
	float pLifeSpan;
};

#endif // !SPIKER_H
