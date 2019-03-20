#include "Flag.h"



Flag::Flag(int sceneIndex_)
{
	sceneIndex = sceneIndex_;
}


Flag::~Flag()
{
}

void Flag::OnCollision(GameObject* other_)
{
	if (other_->GetBoundingBox().Intersects(&other_->GetBoundingBox())) {
		if (other_->GetTag() == "Player")
		{
			//! Player wins
			SceneManager::GetInstance()->SetScene(sceneIndex);
		}
	}
}