#ifndef PICKUP_H
#define PICKUP_H

#include "../../Engine/Rendering/3D/GameObject.h"

class Pickup : public GameObject
{
public:
	Pickup(Model* model_, glm::vec3 position_);
	~Pickup();
	void OnHit(GameObject* gameObject_);
	bool isHit;
};


#endif // !PICKUP_H


