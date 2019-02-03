#include "CollisionHandler.h"
#include "../Core/Engine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionHandlerInstance = nullptr;
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler()
{
}


CollisionHandler::~CollisionHandler()
{
	delete scenePartition;
	scenePartition = nullptr;
}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionHandlerInstance.get() == nullptr)
	{
		collisionHandlerInstance.reset(new CollisionHandler);
	}
	return collisionHandlerInstance.get();
}

void CollisionHandler::Initialize(float worldSize_)
{
	previousCollisions.clear();
	previousCollisions.shrink_to_fit();
	
	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* gameObject_)
{
	scenePartition->AddObject(gameObject_);
}

void CollisionHandler::Update(glm::vec2 mousePosition_, int buttonType_)
{
	Raycast ray = CollisionDetection::ScreenToWorldRay(mousePosition_, Engine::GetInstance()->GetScreenSize());
	GameObject* hitObj = scenePartition->GetCollision(ray);

	if (hitObj)
	{
		hitObj->SetHit(true, buttonType_);
	}

	for (auto p : previousCollisions)
	{
		if (p != hitObj && p != nullptr)
		{
			p->SetHit(false, buttonType_);
		}
	}
	previousCollisions.clear();
	previousCollisions.shrink_to_fit(); ///FLAG: Possibly doesnt need to exist

	if (hitObj)
	{
		previousCollisions.push_back(hitObj);
	}
}
