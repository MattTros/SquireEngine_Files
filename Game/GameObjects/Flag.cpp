#include "Flag.h"



Flag::Flag(Model* model_, glm::vec3 position_, int sceneIndex_) : GameObject(model_, position_)
{
	sceneIndex = sceneIndex_;

	Model* blue = new Model("RedFire.obj", "RedFire.mtl", Shader::GetInstance()->GetShader("baseShader"));
	Model* blue2 = new Model("OrangeFire.obj", "OrangeFire.mtl", Shader::GetInstance()->GetShader("baseShader"));
	Model* smokeModel = new Model("OrangeFire.obj", "OrangeFire.mtl", Shader::GetInstance()->GetShader("alphaShader"));
	fire = new ParticleSystem();
	fire->CreateSystem(blue, blue2, 20, glm::vec3(0.4f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.5f, 0.75f);
	fire->SetOrigin(glm::vec3(position_.x, position_.y - 0.5f, position_.z));
	fire->SetRotationSpeed(3.0f);
	fire->SetRadius(glm::vec3(0.15f));
	fire->StartSystem();

	smoke = new ParticleSystem();
	smoke->CreateSystem(smokeModel, 10, glm::vec3(0.15f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 1.25f);
	smoke->SetOrigin(glm::vec3(position_.x, position_.y - 0.5f, position_.z));
	smoke->SetRotationSpeed(3.0f);
	smoke->SetRadius(glm::vec3(0.1f));
	smoke->StartSystem();

	Model* pit = new Model("FirePit.obj", "FirePit.mtl", Shader::GetInstance()->GetShader("baseShader"));
	firepit = new GameObject(pit, glm::vec3(position_.x, position_.y - 0.5f, position_.z));
	firepit->SetScale(glm::vec3(0.5f));
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
	fire->Update(deltaTime_);
	smoke->Update(deltaTime_);
	firepit->Update(deltaTime_);
}

void Flag::Render(Camera* camera_)
{
	fire->Render(camera_);
	smoke->Render(camera_);
	firepit->GetModel()->Render(camera_);
}