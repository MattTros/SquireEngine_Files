#include "ParallaxingBackground.h"



ParallaxingBackground::ParallaxingBackground()
{
	//! Set defaults for these:
	frontCenterOne = 0.0f;
	frontCenterTwo = 0.0f;
	midCenterOne = 0.0f;
	midCenterTwo = 0.0f;
	backCenter = 0.0f;
}


ParallaxingBackground::~ParallaxingBackground()
{
}

void ParallaxingBackground::Initialize()
{
	//! Create objects and add to scenegraph for the render to control:

	//! Add models to graph:
	SceneGraph::GetInstance()->AddModel(backgroundFront);
	SceneGraph::GetInstance()->AddModel(backgroundFrontTwo);
	SceneGraph::GetInstance()->AddModel(backgroundMid);
	SceneGraph::GetInstance()->AddModel(backgroundMidTwo);
	SceneGraph::GetInstance()->AddModel(backgroundBack);

	//! Create GameObjects from the sceneGraph models we just added:
	SceneGraph::GetInstance()->AddGameObject(new GameObject(backgroundFront), "bFront");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(backgroundFrontTwo), "bFrontTwo");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(backgroundMid), "bMid");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(backgroundMidTwo), "bMidTwo");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(backgroundBack), "bBack");

	//! Manipulate foreground (darker plane)
	SceneGraph::GetInstance()->GetGameObject("bFront")->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("bFront")->SetPosition(glm::vec3(-0.5f, -2.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("bFront")->SetScale(glm::vec3(2.5f, 2.0f, 2.0f));
	SceneGraph::GetInstance()->GetGameObject("bFront")->SetAngle(1.575f);

	//! Make the added-on ground have all the same characteristics of the layer it's copying:
	SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->SetRotation(SceneGraph::GetInstance()->GetGameObject("bFront")->GetRotation());
	SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->SetAngle(SceneGraph::GetInstance()->GetGameObject("bFront")->GetAngle());
	SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->SetScale(SceneGraph::GetInstance()->GetGameObject("bFront")->GetScale());
	SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->SetPosition
	(
		glm::vec3
		(
			//! Make the x position of the add-on at the right edge of the layer it's following:
			SceneGraph::GetInstance()->GetGameObject("bFront")->GetPosition().x +
			SceneGraph::GetInstance()->GetGameObject("bFront")->GetModel()->GetBoundingBox().maxVert.x *
			SceneGraph::GetInstance()->GetGameObject("bFront")->GetScale().x * 2.0,
			SceneGraph::GetInstance()->GetGameObject("bFront")->GetPosition().y,
			SceneGraph::GetInstance()->GetGameObject("bFront")->GetPosition().z
		)
	);

	//! Manipulate the midground (lighter plane):
	SceneGraph::GetInstance()->GetGameObject("bMid")->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("bMid")->SetAngle(1.575f);
	SceneGraph::GetInstance()->GetGameObject("bMid")->SetScale(glm::vec3(2.5f, 2.0f, 2.0f));
	SceneGraph::GetInstance()->GetGameObject("bMid")->SetPosition(glm::vec3(-0.5f, -1.75f, -0.01f));

	//! Make the added-on ground have all the same characteristics of the layer it's copying:
	SceneGraph::GetInstance()->GetGameObject("bMidTwo")->SetRotation(SceneGraph::GetInstance()->GetGameObject("bMid")->GetRotation());
	SceneGraph::GetInstance()->GetGameObject("bMidTwo")->SetAngle(SceneGraph::GetInstance()->GetGameObject("bMid")->GetAngle());
	SceneGraph::GetInstance()->GetGameObject("bMidTwo")->SetScale(SceneGraph::GetInstance()->GetGameObject("bMid")->GetScale());
	SceneGraph::GetInstance()->GetGameObject("bMidTwo")->SetPosition
	(
		glm::vec3
		(
			//! Make the x position of the add-on at the right edge of the layer it's following:
			SceneGraph::GetInstance()->GetGameObject("bMid")->GetPosition().x +
			SceneGraph::GetInstance()->GetGameObject("bMid")->GetModel()->GetBoundingBox().maxVert.x *
			SceneGraph::GetInstance()->GetGameObject("bMid")->GetScale().x * 2.0,
			SceneGraph::GetInstance()->GetGameObject("bMid")->GetPosition().y,
			SceneGraph::GetInstance()->GetGameObject("bMid")->GetPosition().z
		)
	);

	//! Manipulate the background (image, doesn't move):
	SceneGraph::GetInstance()->GetGameObject("bBack")->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("bBack")->SetAngle(-1.575f);
	SceneGraph::GetInstance()->GetGameObject("bBack")->SetPosition(glm::vec3(0.0f, 0.0f, -0.1f));

	//! Set centerpoint for background image:
	backCenter = SceneGraph::GetInstance()->GetGameObject("bBack")->GetPosition().x +
		(SceneGraph::GetInstance()->GetGameObject("bBack")->GetModel()->GetBoundingBox().maxVert.x / 2);
}
	 
void ParallaxingBackground::Update(float deltaTime_)
{
	//! Keyboard controls:
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A))
	{
		//! Player moving left, background move right:
		movingRight = true;

		SceneGraph::GetInstance()->GetGameObject("bFront")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bFront")->GetPosition().x + (deltaTime_ / 2.0f), -2.0f, 0.0f));
		SceneGraph::GetInstance()->GetGameObject("bMid")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bMid")->GetPosition().x + (deltaTime_ / 4.0f), -1.75f, -0.01f));
		SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->GetPosition().x + (deltaTime_ / 2.0f), -2.0f, 0.0f));
		SceneGraph::GetInstance()->GetGameObject("bMidTwo")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bMidTwo")->GetPosition().x + (deltaTime_ / 4.0f), -1.75f, -0.01f));
	}

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D))
	{
		//! Player moving right, background move left:
		movingLeft = true;

		SceneGraph::GetInstance()->GetGameObject("bFront")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bFront")->GetPosition().x + (-deltaTime_ / 2.0f), -2.0f, 0.0f));
		SceneGraph::GetInstance()->GetGameObject("bMid")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bMid")->GetPosition().x + (-deltaTime_ / 4.0f), -1.75f, -0.01f));
		SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->GetPosition().x + (-deltaTime_ / 2.0f), -2.0f, 0.0f));
		SceneGraph::GetInstance()->GetGameObject("bMidTwo")->SetPosition(glm::vec3(SceneGraph::GetInstance()->GetGameObject("bMidTwo")->GetPosition().x + (-deltaTime_ / 4.0f), -1.75f, -0.01f));
	}


	//! Update centerpoints of all the objects:
	frontCenterOne = SceneGraph::GetInstance()->GetGameObject("bFront")->GetPosition().x +
		(SceneGraph::GetInstance()->GetGameObject("bFront")->GetModel()->GetBoundingBox().maxVert.x / 2);
	frontCenterTwo = SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->GetPosition().x +
		(SceneGraph::GetInstance()->GetGameObject("bFrontTwo")->GetModel()->GetBoundingBox().maxVert.x / 2);

	midCenterOne = SceneGraph::GetInstance()->GetGameObject("bMid")->GetPosition().x +
		(SceneGraph::GetInstance()->GetGameObject("bMid")->GetModel()->GetBoundingBox().maxVert.x / 2);
	midCenterTwo = SceneGraph::GetInstance()->GetGameObject("bMidTwo")->GetPosition().x +
		(SceneGraph::GetInstance()->GetGameObject("bMidTwo")->GetModel()->GetBoundingBox().maxVert.x / 2);

	//! Check if centers of backgrounds are at the center of screen:
	if (movingRight)
	{
		//! Backgrounds are moving to the right:

		if (frontCenterOne >= backCenter)
		{
			//! Foreground is too far to the right, move ForegroundTwo's center to the center of the screen
			MoveLeft(SceneGraph::GetInstance()->GetGameObject("bFront"), SceneGraph::GetInstance()->GetGameObject("bFrontTwo"));
		}

		if (midCenterOne >= backCenter)
		{
			//! Background is too far to the right, move backgroundTwo's center to the center of the screen
			MoveLeft(SceneGraph::GetInstance()->GetGameObject("bMid"), SceneGraph::GetInstance()->GetGameObject("bMidTwo"));
		}
	}

	if (movingLeft)
	{
		//! Backgrounds moving left:
		if (backCenter >= frontCenterTwo)
		{
			//! Foreground is too far to the left, move ForegroundTwo's center to the center of the screen
			MoveRight(SceneGraph::GetInstance()->GetGameObject("bFront"), SceneGraph::GetInstance()->GetGameObject("bFrontTwo"));
		}

		if (backCenter >= midCenterTwo)
		{
			//! Background is too far to the right, move backgroundTwo's center to the center of the screen
			MoveRight(SceneGraph::GetInstance()->GetGameObject("bMid"), SceneGraph::GetInstance()->GetGameObject("bMidTwo"));
		}
	}
	
	//! Reset
	movingLeft = false;
	movingRight = false;
}

void ParallaxingBackground::MoveRight(GameObject* objA_, GameObject* objB_)
{
	//! Set a temporary position where A was:
	glm::vec3 tempPos = objA_->GetPosition();

	//! Move A to where B is:
	objA_->SetPosition(glm::vec3
	(
		objB_->GetPosition().x,
		objB_->GetPosition().y,
		objB_->GetPosition().z
	));

	//! Move B over to the right as far as A had to:
	objB_->SetPosition(glm::vec3
	(
		objB_->GetPosition().x + (objA_->GetPosition().x - tempPos.x),
		objB_->GetPosition().y,
		objB_->GetPosition().z
	));
}

void ParallaxingBackground::MoveLeft(GameObject* objA_, GameObject* objB_)
{
	//! Set a temporary position where B was:
	glm::vec3 tempPos = objB_->GetPosition();

	//! Move B to where A is:
	objB_->SetPosition(glm::vec3
	(
		objA_->GetPosition().x,
		objA_->GetPosition().y,
		objA_->GetPosition().z
	));

	//! Move A over to the right as far as B had to:
	objA_->SetPosition(glm::vec3
	(
		objA_->GetPosition().x - (tempPos.x - objB_->GetPosition().x),
		objA_->GetPosition().y,
		objA_->GetPosition().z
	));
}