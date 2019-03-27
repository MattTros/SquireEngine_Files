#include "TutorialCollider.h"

#define MODEL new Model("AttackBox.obj", "AttackBox.mtl", Shader::GetInstance()->GetShader("baseShader"))

TutorialCollider::TutorialCollider(std::string tag_, glm::vec3 position_) : GameObject(MODEL, position_) {
	SetTag(tag_);
	SetPosition(position_);
}

TutorialCollider::~TutorialCollider() {

}

void TutorialCollider::Render(Camera* camera_) {
	this->GetModel()->Render(camera_);
}