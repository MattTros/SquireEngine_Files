#include "Pickup.h"



Pickup::Pickup(Model* model_, glm::vec3 position_) : GameObject(model_, position_)
{
	SetTag("Health");
	SetScale(glm::vec3(0.5));
	SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	isHit = false;
}


Pickup::~Pickup()
{
}

void Pickup::OnHit(GameObject* gameObject_)
{
	if(gameObject_->GetTag() == "Player" && gameObject_->GetBoundingBox().Intersects(&GetBoundingBox()))
		isHit = true;
}
