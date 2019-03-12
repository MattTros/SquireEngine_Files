#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Math/Physics.h"

class GameObject
{
public:
	GameObject(Model* model_);
	GameObject(Model* model_, glm::vec3 position_);
	~GameObject();

	void Update(const float deltaTime_);
	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 position_);
	float GetAngle() const;
	void SetAngle(float angle_);
	glm::vec3 GetRotation() const;
	void SetRotation(glm::vec3 rotation_);
	glm::vec3 GetScale() const;
	void SetScale(glm::vec3 scale_);

	Model* GetModel() const;

	BoundingBox GetBoundingBox() const;
	std::string GetTag();
	void SetTag(std::string tag_);

	void SetHit(bool hit_, int buttonType_);
private:
	Model* model;
	GLuint modelInstance;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	BoundingBox boundingBox;
	std::string tag;

	bool hit;
};

#endif // !GAMEOBJECT_H

