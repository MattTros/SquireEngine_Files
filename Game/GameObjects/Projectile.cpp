#include "Projectile.h"



Projectile::Projectile(Model* model_, glm::vec3 position_, bool isGravity_, float speed_, float lifetime_) : Entity(model_, position_, isGravity_)
{
	SetPosition(position_);
	SetGravity(isGravity_);
	SetSpeed(speed_);
	lifetime = lifetime_;

	currentLifetime = 0.0f;
}


Projectile::~Projectile()
{
	
}

float Projectile::GetCurrentLifetime()
{
	return currentLifetime;
}

float Projectile::GetLifetime()
{
	return lifetime;
}

float Projectile::GetDirection()
{
	return direction;
}

void Projectile::SetLifetime(float lifeTime_)
{
	currentLifetime = lifeTime_;
}

void Projectile::SetDirection(float direction_)
{
	direction = direction_;
}

void Projectile::Update(float deltaTime_)
{
	currentLifetime += deltaTime_;
}

void Projectile::Render(Camera* camera_)
{
	GetModel()->Render(camera_);
}
