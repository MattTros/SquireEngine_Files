#include "Spiker.h"

Spiker::Spiker(Model* model_, glm::vec3 position_, Entity* player_) : Enemy(model_, position_, false) {
	//defaults
	SetHealth(100);
	state = 0;
	player = player_;
	SetTag("Enemy");
	position = position_;
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
	velocity = glm::vec3(0);
	SetGravity(true);
	patrolRight = true;
	SetSpeed(0.2f);
	//iframe stuff
	wfs = WaitForSeconds();
	wfs.waitTime = 0.5f;
	wfs.seconds = 0.0f;
}

Spiker::~Spiker() {

}

void Spiker::Update(const float deltaTime_) {

	if (GetHealth() <= 0) {
		std::cout << "health: " << GetHealth() << std::endl;
	}

	//iframe stuff
	if (wfs.active) {
		if (wfs.seconds >= wfs.waitTime) {
			wfs.seconds = 0.0f;
			wfs.active = false;
		}
		wfs.seconds += deltaTime_;
	}

	//State machine, 0 = Patrol state. 1 = Chase the player state.
	if (state == 0) {
		Patrol(deltaTime_);
	}
	else if (state == 1) {
		Chase(deltaTime_);
	}

	if (GetGravity() == true) {
		velocity += (velocity * deltaTime_) + (0.5f * acceleration * (deltaTime_ * deltaTime_));
		position += velocity * deltaTime_;
		SetPosition(position);
	}

	attackTimer += deltaTime_;

	if (attackTimer >= 5.0f) {
		Attack();
		attackTimer = 0.0f;
	}

	if (shotSpike != nullptr)
	{
		shotSpike->Update(deltaTime_);
		shotSpike->SetPosition(glm::vec3(shotSpike->GetPosition().x + (deltaTime_ * shotSpike->GetSpeed() * shotSpike->GetDirection()), shotSpike->GetPosition().y, shotSpike->GetPosition().z));
		
		//shotSpike->SetPosition(glm::vec3(shotSpike->GetPosition().x + (deltaTime_ * shotSpike->GetSpeed()), shotSpike->GetPosition() + Parabola(shotSpike->GetPosition().x), shotSpike->GetPosition().z));

		if (shotSpike->GetCurrentLifetime() >= shotSpike->GetLifetime())
		{
			shotSpike->~Projectile();

			delete shotSpike;
			shotSpike = nullptr;

			delete spike;
			spike = nullptr;
		}
	}

}

void Spiker::Render(Camera* camera_) {
	GetModel()->Render(camera_);

	if (spike != nullptr)
	{
		spike->Render(camera_);
	}
}

void Spiker::CollisionResponse(GameObject* other_, const float deltaTime_) {
	//call the default collisions from the entity class
	DefaultCollision(other_, deltaTime_);

	if (other_->GetBoundingBox().Intersects(&GetBoundingBox())) {

		if (other_->GetTag() == "Sword") {
			if (!wfs.active) {
				SetHealth(GetHealth() - 50);
				wfs.active = true;
			}
		}

		if (other_->GetTag() == "Wall") {
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
				SetSpeed(0.0f);
				//direction = the normalized distance between the other object and the platform
				glm::vec3 direction = glm::normalize(player->GetPosition() - position);
				SetRotation(glm::vec3(0.0f, direction.x, 0.0f));
			}
		}
		else {
			SetSpeed(0.2f);
		}
	}
}

void Spiker::Patrol(float deltaTime_) {
	SetSpeed(0.2f);
	if (player != nullptr) {
		float distance = glm::length(player->GetPosition() - position);

		if (distance <= 3.0)
			state = 1;
	}

	//Goomba like AI
	float speed = GetSpeed();
	if (patrolRight) {
		SetVelocity(glm::vec3(-GetSpeed(), 0.0f, 0.0f));
		SetRotation(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	else {
		SetVelocity(glm::vec3(GetSpeed(), 0.0f, 0.0f));
		SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	//new position equation applying velocity
	position += GetVelocity() * deltaTime_;

	SetPosition(position);
}

void Spiker::Chase(const float deltaTime_) {
	if (player != nullptr) {
		//Get position
		position = GetPosition();
		//direction = the normalized distance between the other object and the platform
		glm::vec3 direction = glm::normalize(player->GetPosition() - position);
		//velocity equation
		SetVelocity(-GetSpeed() * direction);
		//new position equation applying velocity
		position.x += GetVelocity().x * deltaTime_;
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

void Spiker::Attack()
{
	std::cout << "attack" << std::endl;
	spike = new Model("ProjectileSpike.obj", "ProjectileSpike.mtl", BASE_SHADER);
	shotSpike = new Projectile(spike, glm::vec3(GetPosition().x, GetPosition().y + 0.125f, GetPosition().z), false, 5.0f, 2.0f);

	shotSpike->SetTag("EnemyProjectile");
	shotSpike->SetDirection(GetPosition().x > player->GetPosition().x ? -1 : 1); //If spiker is on the right side, he shoots along the -X-Axis, otherwise he shoots to the right.
	shotSpike->SetRotation(glm::vec3(shotSpike->GetRotation().x, shotSpike->GetDirection(), shotSpike->GetRotation().z));

	//! Parabola work:
	//float x1 = 0.0f; //! X-intercept 1
	//float x2 = 0.0f; //! X-intercept 2

	//glm::vec3 posPlayer = player->GetPosition(); //! Position of player at instance of method call
	//glm::vec3 posEnemy = GetPosition(); //! Position of Spiker at instance of method call

	////! Find the vertex:
	//if (posPlayer.y > posEnemy.y)
	//{
	//	//! Player is higher up than enemy, adjust vertex y value to be higher than player so arc looks natural:
	//	vertex.x = glm::length(posPlayer - posEnemy) / 2.0f; //! This places the vertex's x position halfway between the spiker and player.
	//	vertex.y = posPlayer.y + 0.05f; //! This places the vertex's y position above the higher object, plus a little, to make the arc proper.
	//}
	//else if (posEnemy.y > posPlayer.y)
	//{
	//	//! Spiker is higher than player, adjust vertex's y value to be higher than spiker so arc looks natural:
	//	vertex.x = glm::length(posPlayer - posEnemy) / 2.0f; //! This places the vertex's x position halfway between the spiker and player.
	//	vertex.y = posEnemy.y + 0.05f;
	//}
	//else
	//{
	//	//! Player and Spiker share a y value, so use either or to calcuate based off either height, I'll use players:
	//	vertex.x = glm::length(posPlayer - posEnemy) / 2.0f; //! This places the vertex's x position halfway between the spiker and player.
	//	vertex.y = posPlayer.y + 0.05f; //! This places the vertex's y position above the higher object, plus a little, to make the arc proper.
	//}

	////! Calculate x intercepts (for parabola to form):
	////! (h,k) = vertex(x,y);
	////! too find x intercepts: x = h +- root(k)
	//x1 = vertex.x - glm::sqrt(vertex.y);
	//x2 = vertex.x + glm::sqrt(vertex.y);

	////! Find parabolic equation, to find our y value at x (allows us to set position of an object as it moves towards the player):
	////! Using vertex form: y = a(x-h)^2 + k
	////! Find a (going to use x1):
	////! x1 technically = (x1, 0) because it's on the x-axis.
	////! 0 = a(x1-vertex.x)^2 + vertex.y
	////! vertex.y = a(x1-vertex.x)^2
	////! a = vertex.y / ((x1-vertex.x)^2)
	//a = vertex.y / ((x1 - vertex.x) * (x1 - vertex.x));

	//Parabola(shotSpike->GetPosition().x);
}

float Spiker::Parabola(float x_)
{
	return (a * ((x_ - vertex.x) * (x_ - vertex.x))) + vertex.y; //! The return is equal to the y position @ the x value.
}