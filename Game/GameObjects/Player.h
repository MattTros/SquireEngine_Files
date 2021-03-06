#ifndef PLAYER_H
#define PLAYER_H

#include "../../Engine/Graphics/ParticleSystem.h"
#include "Entity.h"
#include "../../Engine/Events/KeyboardInputManager.h"
#include "../../Engine/Core/Timer.h"
#include "../../Engine/UI/UIManager.h"
#include "../../Engine/UI/PlayerUI.h"
#include "Projectile.h"

class Player : public Entity
{
public:
	Player(Model* model_, GameObject* sword_, glm::vec3 position_);
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
	GameObject* GetAttackBox();

	Projectile* arrow;

	//collision bools
	bool canGoRight;
	bool canGoLeft;
private:
	//UI variables
	UIManager* UI;
	Window* window;

	Model* particle;
	ParticleSystem* fountain;

	GameObject* sword;
	GameObject* attackBox;

	Model* arrowModel;
	bool arrowShooting;

	bool isDashing = false;
	bool isFacingRight = true;
	bool turningRight = false;
	bool turningLeft = false;
	bool iFrames = false;
	bool isAttacking = false;
	int shootingDirection = 1;
	float jumpForce;
	float gravityScale = 3.0f;
	float dashForce = 5.0f;
	bool dashingRight;
	bool dashingLeft;
	bool hittingWall = false;
	bool isDead;
	float speed = 1.5f;
	WaitForSeconds dashTimer;
	WaitForSeconds dashCooldown;
	WaitForSeconds jumpCooldown;
	WaitForSeconds attackTimer;
	WaitForSeconds knockbackTimer;
	WaitForSeconds deathTimer;
};


#endif // !PLAYER_H


