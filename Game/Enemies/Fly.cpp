#include "Fly.h"

Fly::Fly(Model* model_, glm::vec3 position_, Entity* player_) : Enemy(model_, position_, false) {
	state = 0;
	player = player_;
	SetTag("Enemy");
	position = glm::vec3(0);
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	velocity = glm::vec3(0);
	SetSpeed(0.5f);
	angle = 0;
	particleOn = false;	
	particlePos = glm::vec3(0);
}

Fly::~Fly() {
	delete player;
}

void Fly::Update(const float deltaTime_) {
	//State machine, 0 = Patrol state. 1 = Chase the player state.
	switch (state) {
	case 0:
		Patrol(deltaTime_);
		break;
	case 1:
		Chase(deltaTime_);
		break;
	}

}

void Fly::CollisionResponse(GameObject* other_, const float deltaTime_) {
	//if fly touches the player, it can fly through anything else
	if (other_->GetBoundingBox().Intersects(&GetBoundingBox())) {
		if (other_->GetTag() == "Player") {
			Attack();
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

	float distance = glm::length(player->GetPosition() - position);
	if (distance <= 2.0f) {
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
		//check the distance to set the state if the platform is close to it's final position
		float distance = glm::length(player->GetPosition() - position);

		if (distance > 2.0f) {
			state = 0;
		}
	}
}

void Fly::Attack() {
	//The fly exudes a cloud when it get's close enough to the player
	//Activate 
}