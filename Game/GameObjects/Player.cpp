#include "Player.h"



Player::Player(Model* model_, glm::vec3 position_) : Entity(model_, position_, true)
{
	///Particle System Initialization
	particle = new Model("Brick.obj", "Brick.mtl", Shader::GetInstance()->GetShader("baseShader"));
	fountain = new ParticleSystem();
	fountain->CreateSystem(particle, 100, glm::vec3(0.25f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 2.0f);
	fountain->SetOrigin(this->GetPosition());
	fountain->SetRotationSpeed(5.0f);
	fountain->StartSystem();
	///Player Acceleration
	SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
	SetVelocity(glm::vec3(0.0f));
	jumpForce = glm::vec3(0.0f, 500.0f, 0.0f);
	///Dash Cooldown Initialization
	dashCooldown = WaitForSeconds();
	dashCooldown.active = false;
	dashCooldown.waitTime = 1.0f;
	dashCooldown.seconds = 0.0f;
	///Jump Cooldown Initialization
	jumpCooldown = WaitForSeconds();
	jumpCooldown.active = false;
	jumpCooldown.waitTime = 1.0f;
	jumpCooldown.seconds = 0.0f;
}


Player::~Player()
{
	delete fountain;
	fountain = nullptr;
}

void Player::Movement(float deltaTime_)
{
	fountain->SetOrigin(this->GetPosition());
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A))
	{
		SetSpeed(-1.0f);
		SetVelocity(glm::vec3(GetSpeed(), GetVelocity().y, GetVelocity().z));
	}
	else if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D))
	{
		SetSpeed(1.0f);
		SetVelocity(glm::vec3(GetSpeed(), GetVelocity().y, GetVelocity().z));
	}

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_SPACE))
	{
		if (!jumpCooldown.active && !GetGravity())
			Jump(deltaTime_);
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_LSHIFT))
	{
		if (!isDashing)
			Dash();
	}
	SetPosition(GetPosition() + GetVelocity() * deltaTime_);
	if (GetGravity())
		SetVelocity(glm::vec3(0.0f, GetVelocity().y, 0.0f));
	else
		SetVelocity(glm::vec3(0.0f));
}

void Player::Jump(float deltaTime_)
{
	SetGravity(true);
	jumpCooldown.active = true;
}

void Player::Dash()
{
	isDashing = true;
	SetVelocity(glm::vec3(GetVelocity().x + (dashForce * GetSpeed()), GetVelocity().y, GetVelocity().z));
	dashCooldown.active = true;
}

void Player::Combat(float deltaTime_)
{
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_F))
	{
		Shoot();
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_Q))
	{
		HeavyAttack();
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_E))
	{
		LightAttack();
	}
}

void Player::LightAttack()
{

}

void Player::HeavyAttack()
{

}

void Player::Shoot()
{

}

void Player::GroundCollision(GameObject* ground_, float deltaTime_)
{
	DefaultCollision(ground_, deltaTime_);
}

void Player::Update(float deltaTime_)
{
	if (GetGravity())
		SetVelocity(glm::vec3(GetVelocity().x, GetVelocity().y + (GetVelocity().y * deltaTime_) + (0.5f * GetAcceleration().y * (deltaTime_ * deltaTime_)), GetVelocity().z));
	if (isDashing)
	{
		dashCooldown.seconds += deltaTime_;
		if (dashCooldown.seconds > dashCooldown.waitTime)
		{
			isDashing = false;
			dashCooldown.seconds = 0.0f;
		}
	}
	if (jumpCooldown.active)
	{
		jumpCooldown.seconds += deltaTime_;
		SetVelocity(glm::vec3(GetVelocity().x, GetVelocity().y + (GetVelocity().y * deltaTime_) + (0.5f * jumpForce.y * (deltaTime_ * deltaTime_)), GetVelocity().z));
		if (jumpCooldown.seconds > jumpCooldown.waitTime)
		{
			jumpCooldown.active = false;
			SetGravity(true);
			SetVelocity(glm::vec3(GetVelocity().x, 0.0f, GetVelocity().z));
			jumpCooldown.seconds = 0.0f;
		}
	}
	Movement(deltaTime_);
	Combat(deltaTime_);
	fountain->Update(deltaTime_);
}

void Player::Render(Camera* camera_)
{
	this->GetModel()->Render(camera_);
	fountain->Render(camera_);
}
