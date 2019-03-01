#ifndef PLAYER_H
#define PLAYER_H

#include "../../Engine/Graphics/ParticleSystem.h"
#include "Entity.h"
#include "../../Engine/Events/KeyboardInputManager.h"
#include "../../Engine/Core/Timer.h"

class Player : public Entity
{
public:
	Player(Model* model_, glm::vec3 position_);
	~Player();

	void Movement(float deltaTime_);
	void Jump(float deltaTime_);
	void Dash();

	void Combat(float deltaTime_);
	void LightAttack();
	void HeavyAttack();
	void Shoot();

	void GroundCollision(GameObject* ground_, float deltaTime_);
	void Update(float deltaTime_);
	void Render(Camera* camera_);
private:
	Model* particle;
	ParticleSystem* fountain;

	GameObject* sword;
	GameObject* arrow;

	bool isDashing = false;
	glm::vec3 jumpForce;
	float dashForce = 10.0f;
	WaitForSeconds dashCooldown;
	WaitForSeconds jumpCooldown;
};


#endif // !PLAYER_H


