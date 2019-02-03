#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>

struct Rigidbody
{
	float gravityScale;
	float mass;
	glm::vec3 velocity;

	inline Rigidbody()
	{
		gravityScale = 1.0f;
		mass = 1.0f;
		velocity = glm::vec3(0.0f);
	}

	inline void AddForce(glm::vec3 force_)
	{
		velocity += force_ / mass;
	}
};

class Physics
{
public:
	Physics();
	~Physics();
};

#endif // !PHYSICS_H



