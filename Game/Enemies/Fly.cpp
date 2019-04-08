#include "Fly.h"

Fly::Fly(Model* model_, glm::vec3 position_, Player* player_) : Enemy(model_, position_, false) {
	SetHealth(100);
	state = 0;
	player = player_;
	SetTag("Enemy");
	position = glm::vec3(0);
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	velocity = glm::vec3(0);
	SetSpeed(0.5f);
	angle = 0;
	//Attacking variables
	attackModel = new Model("AttackBox.obj", "AttackBox.mtl", Shader::GetInstance()->GetShader("baseShader"));
	attackBox = new GameObject(attackModel, glm::vec3(position_.x, position_.y, position_.z - 10));
	attackBox->SetTag("Gas");
	knockedBack = false;
	isAttacking = false;
	attackTimer = 0.0f;
	gasPos = glm::vec3();
	//Particle variables
	particle = new Model("GasBubble.obj", "GasBubble.mtl", Shader::GetInstance()->GetShader("alphaShader"));
	particle->GetMesh(0)->transparency = 0.3f;
	fountain = new ParticleSystem();
	fountain->CreateSystem(particle, 20, glm::vec3(0.5f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.2f, 0.4f);
	fountain->SetRadius(glm::vec3(0.5f));
	fountain->SetOrigin(attackBox->GetPosition());
	fountain->SetRotationSpeed(5.0f);
	fountain->StartSystem();
}

Fly::~Fly() {
	delete fountain;
	fountain = nullptr;
}

void Fly::Update(const float deltaTime_) {
	
	fountain->Update(deltaTime_);
	fountain->SetOrigin(gasPos);

	if (isAttacking) {
		//increment timer
		attackTimer += deltaTime_;
		
		//knockback reset
		//atack begins
		if (attackTimer >= 1.0f) {
			Attack();
			knockedBack = false;
		}
		
		//stop attacking
		if (attackTimer >= 5.0f) {
			isAttacking = false;
			attackTimer = 0.0f;
			attackBox->SetPosition(glm::vec3(GetVelocity().x, GetVelocity().y, -10.0f));
		}
	}

	//State machine, 0 = Patrol state. 1 = Chase the player state.
	attackBox->Update(deltaTime_);
	if (!knockedBack) {
		switch (state) {
		case 0:
			Patrol(deltaTime_);
			break;
		case 1:
			Chase(deltaTime_);
			break;
		}
	}
	else {
		Knockback(deltaTime_);
	}
}

void Fly::Render(Camera* camera_) {
	GetModel()->Render(camera_);
	if (isAttacking) {
		//attackBox->GetModel()->Render(camera_);
		fountain->Render(camera_);
	}
}

void Fly::CollisionResponse(GameObject* other_, const float deltaTime_) {
	//if fly touches the player or is attacked, it can fly through anything else
	if (other_->GetBoundingBox().Intersects(&GetBoundingBox())) {
		if (other_->GetTag() == "AttackBox" || other_->GetTag() == "Player" || other_->GetTag() == "FriendlyProjectile") {
			isAttacking = true;
			attackTimer = 0.0f;
			gasPos = GetPosition();
			
			if (player->GetPosition().x - GetPosition().x > 0.0f) {
				knockbackDirection = -1;
				knockedBack = true;
			}
			else {
				knockbackDirection = 1;
				knockedBack = true;
			}
		}

		if (other_->GetTag() == "AttackBox" || (other_->GetTag() == "FriendlyProjectile" && player->arrow->canDamage)) {
			AudioManager::GetInstance()->PlaySoundFX("hit", 0, 1);
			SetHealth(GetHealth() - 25.0f);
			if (other_->GetTag() == "FriendlyProjectile")
				player->arrow->canDamage = false;
		}
	}
}

void Fly::Patrol(const float deltaTime_) {
	//determine the direction the fly is facing

	//flutter idle code
	position = GetPosition();
	position.y += (sin(angle) * deltaTime_) / 2;
	angle++;
	if (angle == 360) {
		angle = 0;
	}
	SetPosition(position);

	//check to see if chasing
	float distance = glm::length(player->GetPosition() - position);
	if (distance <= 5.0f) {
		state = 1;
	}

}

void Fly::Chase(const float deltaTime_) {
	if (player != nullptr) {
		//Get position
		position = GetPosition();
		//direction = the normalized distance between the other object and the platform
		glm::vec3 direction = glm::normalize(player->GetPosition() - position);
		//velocity equation
		SetVelocity(GetSpeed() * direction);

		//new position equation applying velocity
		position += GetVelocity() * deltaTime_;
		if (GetVelocity().x > 0) {
			SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			SetRotation(glm::vec3(0.0f, -1.0f, 0.0f));
		}

		SetPosition(position);
		//check the distance to set the state
		float distance = glm::length(player->GetPosition() - position);

		if (distance > 5.0f) {
			state = 0;
		}
	}
}

void Fly::Attack() {
	//The fly exudes a cloud when it get's close enough to the player
	//Activate the gas
	attackBox->SetPosition(gasPos);
	attackBox->GetModel()->Render(Camera::GetInstance());
	fountain->Render(Camera::GetInstance());

}

GameObject* Fly::GetGas() {
	return attackBox;
}

void Fly::Knockback(const float deltaTime_) {
	//apply force in the direction that the fly is hit
	SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	SetVelocity(glm::vec3(GetVelocity().x + (1.0f * knockbackDirection), GetVelocity().y, GetVelocity().z));
	SetPosition(GetPosition() + GetVelocity() * deltaTime_);
}