#include "Flag.h"



Flag::Flag(Model* model_, glm::vec3 position_, int sceneIndex_) : GameObject(model_, position_)
{
	sceneIndex = sceneIndex_;
}


Flag::~Flag()
{
}

void Flag::OnCollision(GameObject* other_)
{
	if (other_->GetBoundingBox().Intersects(&GetBoundingBox())) {
		if (other_->GetTag() == "Player")
		{
			//! Player wins
			SceneManager::GetInstance()->SetScene(sceneIndex);
		}
	}
}

void Flag::Update(float deltaTime_)
{

}

void Flag::Render(Camera* camera_)
{

}