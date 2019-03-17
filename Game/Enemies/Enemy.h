#ifndef ENEMY_H
#define ENEMY_H

#include "../GameObjects/Entity.h"

class Enemy : public Entity {
public:
	inline Enemy(Model* model_, glm::vec3 position_, bool isGravity_) : Entity(model_, position_, isGravity_) {

	}

	~Enemy() {}

	virtual void Update(const float deltaTime_) = 0;
	virtual void CollisionResponse(GameObject* other_, const float deltaTime_) = 0;

private:
	//publc methods
	virtual void Patrol(const float deltaTime_) = 0;
	virtual void Chase(const float deltaTime_) = 0;
	virtual void Attack() = 0;

};

#endif //ENEMY_H