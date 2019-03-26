#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(Model* model_, glm::vec3 position_, bool isGravity_, float speed_, float lifetime_);
	~Projectile();

	float GetCurrentLifetime();
	float GetLifetime();
	float GetDirection();
	void SetDirection(float direction_);
	void Update(float deltaTime_);
	void Render(Camera* camera_);
private:
	float lifetime;
	float currentLifetime;
	float direction;
};

#endif // !PROJECTILE_H