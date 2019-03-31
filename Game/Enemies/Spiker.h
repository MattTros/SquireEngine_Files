#ifndef SPIKER_H
#define SPIKER_H

//Class by Jake G. Cunningham

#include "Enemy.h"
#include "../GameObjects/Projectile.h"

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

class Spiker : public Enemy {

public:
	Spiker(Model* model_, glm::vec3 position_, Entity* player_);
	~Spiker();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);
	void CollisionResponse(GameObject* other_, const float deltaTime_);

	float a = 0.0f; //! Value a (needed to find y)
	float y = 0.0f; //! Final y value at point x
	glm::vec2 vertex = glm::vec2(); //! Vertex, set to default glm::vec2()

	Projectile* shotSpike;
private:
	//private methods
	void Patrol(const float deltaTime_);
	//Avoid the player
	void Chase(const float deltaTime_);

	void Attack();
	float Parabola(float x_);
	
	Model* spike;
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
	float attackTimer;

	//attack variables
	GameObject* projectile;
	float pLifeSpan;
};

#endif // !SPIKER_H