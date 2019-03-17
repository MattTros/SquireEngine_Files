#ifndef PLAYER_H
#define PLAYER_H

#include "../../Engine/Graphics/ParticleSystem.h"
#include "Entity.h"
#include "../../Engine/Events/KeyboardInputManager.h"
#include "../../Engine/Core/Timer.h"

class Player : public Entity
{
public:
	Player(Model* model_, GameObject* sword_, GameObject* arrow_, glm::vec3 position_);
	~Player();

	void Movement(float deltaTime_);
	void Jump();
	void Dash();

	void Combat(float deltaTime_);
	void LightAttack(float zAxisRotation_);
	void HeavyAttack();
	void Shoot();

	bool GetIFrames();
	void SetIFrames(bool iFrames_);

	void PlayerCollision(GameObject* other_, float deltaTime_);

	void Update(float deltaTime_);
	void Render(Camera* camera_);

	//sword getter
	GameObject* GetSword();

private:
	Model* particle;
	ParticleSystem* fountain;

	GameObject* sword;
	GameObject* arrow;

	//Rigidbody rb;

	bool isDashing = false;
	bool isFacingRight = true;
	bool iFrames = false;
	bool isAttacking = false;
	float jumpForce;
	float dashForce = 5.0f;
	WaitForSeconds dashTimer;
	WaitForSeconds dashCooldown;
	WaitForSeconds jumpCooldown;
	WaitForSeconds attackTimer;

	//collision bools
	bool canGoRight;
	bool canGoLeft;
};


#endif // !PLAYER_H


