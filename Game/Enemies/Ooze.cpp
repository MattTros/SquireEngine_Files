#include "Ooze.h"

Ooze::Ooze(Model* model_, glm::vec3 position_, bool isGravity_, Entity* player_) : Enemy(model_, position_, isGravity_) {
	//defaults
	SetHealth(100);
	state = 0;
	player = player_;
	SetTag("Enemy");
	position = position_;
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	velocity = glm::vec3(0);
	SetGravity(isGravity_);
	patrolRight = true;
	SetSpeed(0.2f);
	//iframe stuff
	wfs = WaitForSeconds();
	wfs.waitTime = 0.5f;
	wfs.seconds = 0.0f;
}

Ooze::~Ooze() {

}

void Ooze::Update(const float deltaTime_) {

	if (GetHealth() <= 0) {
		std::cout << "health: " << GetHealth() << std::endl;
	}

	//iframe stuff
	if (wfs.active) {
		wfs.seconds += deltaTime_;
		SetVelocity(glm::vec3(0.0f, GetVelocity().y, 0.0f));
		SetVelocity(glm::vec3(GetVelocity().x + (2.0f * knockBackDirection), GetVelocity().y, GetVelocity().z));
		SetPosition(GetPosition() + GetVelocity() * deltaTime_);
		if (wfs.seconds >= wfs.waitTime) {
			wfs.seconds = 0.0f;
			wfs.active = false;
		}
	}

	//State machine, 0 = Patrol state. 1 = Chase the player state.
	if (state == 0 && !wfs.active) {
		Patrol(deltaTime_);
	}
	else if (state == 1 && !wfs.active) {
		Chase(deltaTime_);
	}

	if (GetGravity() == true) {
		velocity += (velocity * deltaTime_) + (0.5f * acceleration * (deltaTime_ * deltaTime_));
		position += velocity * deltaTime_;
		SetVelocity(glm::vec3(GetVelocity().x, velocity.y, GetVelocity().z));
		SetPosition(position);
	}
}

void Ooze::Render(Camera* camera_) {
	GetModel()->Render(camera_);
}

void Ooze::CollisionResponse(GameObject* other_, const float deltaTime_) {
	//call the default collisions from the entity class
	DefaultCollision(other_, deltaTime_);

	if (other_->GetBoundingBox().Intersects(&GetBoundingBox())) {

		if (other_->GetTag() == "AttackBox" || other_->GetTag() == "FriendlyProjectile"){
			if (!wfs.active) {
				SetHealth(GetHealth() - 25);
				wfs.active = true;
				if (player->GetPosition().x - GetPosition().x > 0.0f)
					knockBackDirection = -1.0f;
				else
					knockBackDirection = 1.0f;
			}
		}


		if (other_->GetTag() == "Wall" || other_->GetTag() == "Player") {

			if (other_->GetTag() == "Wall") {
				wfs.seconds = 0.5f;
			}

			//Collision for if patrolling
			if (GetSpeed() == 0.0f) {
				SetSpeed(0.2f);
			}
			if (state == 0) {
				SetSpeed(0.2f);
				if (patrolRight == true) {
					patrolRight = false;
					SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
				}
				else {
					patrolRight = true;
					SetRotation(glm::vec3(0.0f, -1.0f, 0.0f));
				}
				//collision for if chasing
			}
			else {
				//calculate which side of the wall and player the ooze is on
				float playerDist = player->GetPosition().x - GetPosition().x;
				float platformDist = other_->GetPosition().x - GetPosition().x;

				if (playerDist > 0 && platformDist > 0) {
					SetSpeed(0.0f);
				}
				else if (playerDist < 0 && platformDist < 0) {
					SetSpeed(0.0f);
				}
				else if (playerDist > 0 && platformDist < 0) {
					SetSpeed(0.2f);
				}
				else if (playerDist < 0 && platformDist > 0) {
					SetSpeed(0.2f);
				}
			}
		}
		else {
			SetSpeed(0.2f);
		}
		
	}
}

void Ooze::Patrol(const float deltaTime_) {
	SetSpeed(0.2f);
	if (player != nullptr) {
		float distance = glm::length(player->GetPosition() - position);

		if (distance <= 3.0)
			state = 1;
	}

	//Goomba like AI
	float speed = GetSpeed();
	if (patrolRight) {
		SetSpeed(-0.2f);
		SetVelocity(glm::vec3(GetSpeed(), 0.0f, 0.0f));
		SetRotation(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	else {
		SetSpeed(0.2f);
		SetVelocity(glm::vec3(GetSpeed(), 0.0f, 0.0f));
		SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	//new position equation applying velocity
	position += GetVelocity() * deltaTime_;

	SetPosition(position);
}

void Ooze::Chase(const float deltaTime_) {
	if (player != nullptr) {
		//Get position
		position = GetPosition();
		//direction = the normalized distance between the other object and the platform
		glm::vec3 direction = glm::normalize(player->GetPosition() - position);
		//velocity equation
		SetVelocity(GetSpeed() * direction);
		//new position equation applying velocity
		position += glm::vec3(GetVelocity().x, 0.0f, 0.0f) * deltaTime_;
		if (GetVelocity().x > 0) {
			SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			SetRotation(glm::vec3(0.0f, -1.0f, 0.0f));
		}

		SetPosition(position);
		//check the distance to set the state if the platform is close to it's final position
		float distance = glm::length(player->GetPosition() - position);

		if (distance > 3.0f) {
			state = 0;
		}
	}
}


void Ooze::Attack() {

}
