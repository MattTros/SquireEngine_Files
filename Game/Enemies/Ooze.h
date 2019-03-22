#ifndef OOZE_H
#define OOZE_H

//Class by Jake G. Cunningham

#include "../Enemies/Enemy.h"

class Ooze : public Enemy {

public:
	Ooze(Model* model_, glm::vec3 position_, bool isGravity_, Entity* player_);
	~Ooze();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);
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
	int knockBackDirection;


	//variable to decide what state the enemy is in
	int state;
	bool patrolRight;

	//iframe stuff
	WaitForSeconds wfs;

};

#endif //OOZE_H