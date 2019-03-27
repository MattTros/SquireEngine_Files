#ifndef TUTORIAL_COLLIDER
#define TUTORIAL_COLLIDER

#include "../../Engine/Rendering/3D/GameObject.h"

class TutorialCollider : public GameObject {
public:
	TutorialCollider(std::string tag_, glm::vec3 position_);
	~TutorialCollider();

	void Render(Camera* camera_);
};

#endif // !TUTORIAL_COLLIDER
