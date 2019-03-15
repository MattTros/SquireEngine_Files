#include "Player.h"



Player::Player(Model* model_, GameObject* sword_, GameObject* arrow_, glm::vec3 position_) : Entity(model_, position_, true)
{
	///Particle System Initialization
	particle = new Model("KnightParticle.obj", "KnightParticle.mtl", Shader::GetInstance()->GetShader("baseShader"));
	fountain = new ParticleSystem();
	fountain->CreateSystem(particle, 100, glm::vec3(0.5f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 2.0f);
	fountain->SetRadius(0.25f);
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
	///Sword Inititalization
	sword = sword_;
	sword->SetTag("Sword");
	sword->SetRotation(glm::vec3(0.0f, 0.0f, 1.0f));
	sword->SetAngle(1.0f);
	attackTimer = WaitForSeconds();
	attackTimer.active = false;
	attackTimer.waitTime = 0.5f;
	attackTimer.seconds = 0.0f;
	//collision bool init
	canGoLeft = true;
	canGoRight = true;
}


Player::~Player()
{
	delete fountain;
	fountain = nullptr;
}

void Player::Movement(float deltaTime_)
{
	fountain->SetOrigin(this->GetPosition());
	sword->SetPosition(this->GetPosition());
	Camera::GetInstance()->SetPosition(glm::vec3(this->GetPosition().x, this->GetPosition().y, Camera::GetInstance()->GetPosition().z));
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A) && canGoLeft)
	{
		if (!GetGravity())
			SetSpeed(-1.0f);
		else
			SetSpeed(-1.0f);
		if(!isDashing)
			SetVelocity(glm::vec3(GetSpeed(), GetVelocity().y, GetVelocity().z));
		if (isFacingRight)
		{
			SetAngle(-1.575);
			isFacingRight = false;
		}
		if(canGoRight == false)
			canGoRight = true;
	}
	else if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D) && canGoRight)
	{
		if (!GetGravity())
			SetSpeed(1.0f);
		else
			SetSpeed(1.0f);
		if (!isDashing)
			SetVelocity(glm::vec3(GetSpeed(), GetVelocity().y, GetVelocity().z));
		if (!isFacingRight)
		{
			SetAngle(1.575);
			isFacingRight = true;
		}
		if (canGoLeft == false)
			canGoLeft = true;
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
	//SetGravity(true);
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
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_RIGHT))
	{
		LightAttack(-1.0f);
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_LEFT))
	{
		LightAttack(1.0f);
	}

	if (isAttacking)
		sword->Update(deltaTime_);
}

void Player::LightAttack(float zAxisRotation_)
{
	if (!isAttacking)
	{
		isAttacking = true;
		attackTimer.active = true;
		sword->SetRotation(glm::vec3(0.0f, 0.0f, zAxisRotation_));
	}
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
	if (ground_->GetBoundingBox().Intersects(&GetBoundingBox())) {
		if (ground_->GetTag() == "Platform") {
			//Collision with specific object response

			glm::vec3 distance = GetPosition() - ground_->GetPosition();
			//length of the platform
			glm::vec3 platLength = abs(ground_->GetBoundingBox().minVert - ground_->GetBoundingBox().maxVert);
			//length of this object
			glm::vec3 thisLength = abs(GetBoundingBox().minVert - GetBoundingBox().maxVert);

			if (distance.y <= ((platLength.y + (thisLength.y / 2)) / 2.0f)) {
				std::cout << "down" << std::endl;
				//glm::vec3 vel = glm::vec3(GetVelocity().x, 0.0f, GetVelocity().z);
				jumpCooldown.seconds = 2.0f;
				//SetVelocity(vel);

				//distance needs to be positive
				glm::vec3 positiveDist = abs(GetPosition() - ground_->GetPosition());

				//if you are on the side of the platform
				if (positiveDist.x >= ((platLength.x + (thisLength.x / 2)) / 2.0f)) {
					if (distance.x < ((platLength.x + (thisLength.x / 2)) / 2.0f)) {
						canGoRight = false;
						dashTimer.seconds = 1.0f;
						jumpCooldown.seconds = 0.0f;
					}

					if (distance.x > ((platLength.x + (thisLength.x / 2)) / 2.0f)) {
						canGoLeft = false;
						dashTimer.seconds = 1.0f;
						jumpCooldown.seconds = 0.0f;
					}
				}
			}
		}
	}

}

void Player::WallCollision(GameObject* wall_, float deltaTime_)
{

}

void Player::Update(float deltaTime_)
{
	Entity::Update(deltaTime_);

	if (GetGravity())
		SetVelocity(glm::vec3(GetVelocity().x, GetVelocity().y + (GetVelocity().y * deltaTime_) + (0.5f * (GetAcceleration().y * 4) * (deltaTime_ * deltaTime_)), GetVelocity().z));
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
		SetVelocity(glm::vec3(GetVelocity().x, 0.0f, GetVelocity().z));
		SetVelocity(glm::vec3(GetVelocity().x, GetVelocity().y + jumpForce, GetVelocity().z));
		jumpCooldown.seconds += deltaTime_;
		if (jumpCooldown.seconds >= jumpCooldown.waitTime)
		{
			SetVelocity(glm::vec3(GetVelocity().x, 0.0f, GetVelocity().z));
			SetGravity(true);
			jumpCooldown.active = false;
			jumpCooldown.seconds = 0.0f;
			canGoLeft = true;
			canGoRight = true;
		}
	}
	if (attackTimer.active)
	{
		sword->SetAngle(sword->GetAngle() + (deltaTime_ * 2.0f));
		attackTimer.seconds += deltaTime_;
		if (attackTimer.seconds >= attackTimer.waitTime)
		{
			isAttacking = false;
			attackTimer.active = false;
			attackTimer.seconds = 0.0f;
			sword->SetAngle(1.0f);
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
	if (isAttacking)
		sword->GetModel()->Render(Camera::GetInstance());
}
