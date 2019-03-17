#ifndef FLY_H
#define FLY_H

//Class by Jake G. Cunningham
#include "Enemy.h"

class Fly : public Enemy {
public:
	Fly(Model* model_, glm::vec3 position_, Entity* player_);
	~Fly();

	void Update(const float deltaTime_);
	void CollisionResponse(GameObject* other_, const float deltaTime_);

private:
	//publc methods
	void Patrol(const float deltaTime_);
	void Chase(const float deltaTime_);
	void Attack();

	//player object that gets passed into the constructor
	Entity* player;

	//temp physics variable
	glm::vec3 position;
	glm::vec3 acceleration;
	glm::vec3 velocity;

	//State variables
	int state;

	//Particle Variables
	glm::vec3 particlePos;
	bool particleOn;

	//Angle for sin wave movement
	int angle;

};

#endif // !FLY_H
