#include "Player.h"



Player::Player(Model* model_, GameObject* sword_, GameObject* arrow_, glm::vec3 position_) : Entity(model_, position_, true)
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
	jumpForce = 1.0f;
	///Dash Cooldown Initialization
	dashCooldown = WaitForSeconds();
	dashCooldown.active = false;
	dashCooldown.waitTime = 1.0f;
	dashCooldown.seconds = 0.0f;
	///Dash Timer Initialization
	dashTimer = WaitForSeconds();
	dashTimer.active = false;
	dashTimer.waitTime = 0.5f;
	dashTimer.seconds = 0.0f;
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
	Camera::GetInstance()->SetPosition(glm::vec3(this->GetPosition().x, this->GetPosition().y, Camera::GetInstance()->GetPosition().z));
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A))
	{
		if (!GetGravity())
			SetSpeed(-1.0f);
		else
			SetSpeed(GetSpeed());
		if(!isDashing)
			SetVelocity(glm::vec3(GetSpeed(), GetVelocity().y, GetVelocity().z));
		if (isFacingRight)
		{
			SetAngle(-1.575);
			isFacingRight = false;
		}
	}
	else if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D))
	{
		if (!GetGravity())
			SetSpeed(1.0f);
		else
			SetSpeed(GetSpeed());
		if (!isDashing)
			SetVelocity(glm::vec3(GetSpeed(), GetVelocity().y, GetVelocity().z));
		if (!isFacingRight)
		{
			SetAngle(1.575);
			isFacingRight = true;
		}
	}

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_SPACE))
	{
		if (!jumpCooldown.active && !GetGravity())
			Jump();
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_LSHIFT))
	{
		if (!isDashing && !dashCooldown.active)
			Dash();
	}
	SetPosition(GetPosition() + GetVelocity() * deltaTime_);
	if (GetGravity())
		SetVelocity(glm::vec3(0.0f, GetVelocity().y, 0.0f));
	else
		SetVelocity(glm::vec3(0.0f));
}

void Player::Jump()
{
	SetGravity(true);
	jumpCooldown.active = true;
}

void Player::Dash()
{
	std::cout << "Dashed" << std::endl;
	isDashing = true;
	dashTimer.active = true;
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

bool Player::GetIFrames()
{
	return iFrames;
}

void Player::SetIFrames(bool iFrames_)
{
	iFrames = iFrames_;
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
		dashTimer.seconds += deltaTime_;
		SetVelocity(glm::vec3(GetVelocity().x + (dashForce * GetSpeed()), GetVelocity().y, GetVelocity().z));
		if (dashTimer.seconds > dashTimer.waitTime)
		{
			dashTimer.active = false;
			isDashing = false;
			dashCooldown.active = true;
			dashTimer.seconds = 0.0f;
		}
	}
	if (dashCooldown.active)
	{
		dashCooldown.seconds += deltaTime_;
		if (dashCooldown.seconds > dashCooldown.waitTime)
		{
			dashCooldown.active = false;
			dashCooldown.seconds = 0.0f;
		}
	}
	
	if (jumpCooldown.active)
	{
		SetVelocity(glm::vec3(GetVelocity().x, GetVelocity().y + jumpForce, GetVelocity().z));
		jumpCooldown.seconds += deltaTime_;
		if (jumpCooldown.seconds >= jumpCooldown.waitTime)
		{
			SetVelocity(glm::vec3(GetVelocity().x, 0.0f, GetVelocity().z));
			SetGravity(true);
			jumpCooldown.active = false;
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
