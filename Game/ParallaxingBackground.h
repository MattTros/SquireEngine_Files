#ifndef PARALLAXINGBACKGROUND_H
#define PARALLAXINGBACKGROUND_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "../../GameEngine/Engine/Core/Engine.h"
class Engine;

class ParallaxingBackground
{
public:
	ParallaxingBackground();
	~ParallaxingBackground();

	void Initialize();
	void Update(float deltaTime_);
	void Render(Camera* camera_);
	glm::vec3 cameraPos = glm::vec3();

	GameObject* bFront;
	GameObject * bFrontTwo;
	GameObject* bMid;
	GameObject* bMidTwo;
	GameObject * bBack;

private:
	Model* backgroundFront = new Model("FrontRocks.obj", "FrontRocks.mtl", BASE_SHADER);
	Model* backgroundFrontTwo = new Model("FrontRocks.obj", "FrontRocks.mtl", BASE_SHADER);
	Model* backgroundMid = new Model("BackRocks.obj", "BackRocks.mtl", BASE_SHADER);
	Model* backgroundMidTwo = new Model("BackRocks.obj", "BackRocks.mtl", BASE_SHADER);
	Model* backgroundBack = new Model("Background.obj", "Background.mtl", BASE_SHADER);

	float frontCenterOne;
	float frontCenterTwo;
	float midCenterOne;
	float midCenterTwo;
	float backCenter;

	bool movingRight = false;
	bool movingLeft = false;

	void MoveRight(GameObject* obj_, GameObject* objB_);
	void MoveLeft(GameObject* objA_, GameObject* objB_);
};

#endif