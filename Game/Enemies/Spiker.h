#ifndef SPIKER_H
#define SPIKER_H

//Class by Jake G. Cunningham

#include "Enemy.h"

class Spiker : public Enemy {

public:
	Spiker();
	~Spiker();

private:
	//publc methods
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
};

#endif // !SPIKER_H
