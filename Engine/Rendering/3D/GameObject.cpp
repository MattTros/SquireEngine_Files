#include "GameObject.h"



GameObject::GameObject(Model* model_)
{
	///Variable Defaults
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	hit = false;

	model = model_;
	tag = "";

	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

GameObject::GameObject(Model* model_, glm::vec3 position_)
{
	///Variable Defaults
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	hit = false;

	model = model_;
	position = position_;
	tag = "";

	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

GameObject::~GameObject()
{
	model = nullptr;
}

void GameObject::Update(const float delataTime_)
{
	
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;	
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

float GameObject::GetAngle() const
{
	return angle;
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);

		boundingBox.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		boundingBox.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

Model* GameObject::GetModel() const
{
	return model;
}

BoundingBox GameObject::GetBoundingBox() const
{
	return boundingBox;
}

std::string GameObject::GetTag()
{
	return tag;
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetHit(bool hit_, int buttonType_)
{
	hit = hit_;
	if (hit)
	{
		std::cout << tag << " Was Hit" << std::endl;
	}
}
