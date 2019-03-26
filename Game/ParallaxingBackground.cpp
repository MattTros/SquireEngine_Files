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
	//! Create GameObjects:
	bFront = new GameObject(backgroundFront);
	bFrontTwo = new GameObject(backgroundFrontTwo);
	bMid = new GameObject(backgroundMid);
	bMidTwo = new GameObject(backgroundMidTwo);
	bBack = new GameObject(backgroundBack);

	//! Manipulate foreground (darker plane)
	bFront->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
	bFront->SetPosition(glm::vec3(-0.5f, -2.0f, -1.0f));
	bFront->SetScale(glm::vec3(3.0f, 2.0f, 2.0f));
	bFront->SetAngle(1.575f);

	//! Make the added-on ground have all the same characteristics of the layer it's copying:
	bFrontTwo->SetRotation(bFront->GetRotation());
	bFrontTwo->SetAngle(bFront->GetAngle());
	bFrontTwo->SetScale(bFront->GetScale());
	bFrontTwo->SetPosition
	(
		glm::vec3
		(
			//! Make the x position of the add-on at the right edge of the layer it's following:
			bFront->GetPosition().x +
			bFront->GetModel()->GetBoundingBox().maxVert.x *
			bFront->GetScale().x * 2.0,
			bFront->GetPosition().y,
			bFront->GetPosition().z
		)
	);

	//! Manipulate the midground (lighter plane):
	bMid->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
	bMid->SetAngle(1.575f);
	bMid->SetScale(glm::vec3(3.0f, 2.0f, 2.0f));
	bMid->SetPosition(glm::vec3(-0.5f, -1.75f, -1.01f));

	//! Make the added-on ground have all the same characteristics of the layer it's copying:
	bMidTwo->SetRotation(bMid->GetRotation());
	bMidTwo->SetAngle(bMid->GetAngle());
	bMidTwo->SetScale(bMid->GetScale());
	bMidTwo->SetPosition
	(
		glm::vec3
		(
			//! Make the x position of the add-on at the right edge of the layer it's following:
			bMid->GetPosition().x +
			bMid->GetModel()->GetBoundingBox().maxVert.x *
			bMid->GetScale().x * 2.0,
			bMid->GetPosition().y,
			bMid->GetPosition().z
		)
	);

	//! Manipulate the background (image, doesn't move):
	bBack->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
	bBack->SetAngle(-1.575f);
	bBack->SetPosition(glm::vec3(0.0f, 0.0f, -1.1f));
	bBack->SetScale(glm::vec3(3.0f));
}
	 
void ParallaxingBackground::Update(float deltaTime_)
{
	cameraPos = Camera::GetInstance()->GetPosition();
	bBack->SetPosition(cameraPos);
	//! Set centerpoint for background image:
	backCenter = bBack->GetPosition().x + (bBack->GetModel()->GetBoundingBox().maxVert.x / 2);
	bFront->SetPosition(glm::vec3(bFront->GetPosition().x, cameraPos.y - 1.3f, bFront->GetPosition().z));
	bMid->SetPosition(glm::vec3(bMid->GetPosition().x, cameraPos.y - 1.05f, bMid->GetPosition().z));
	bFrontTwo->SetPosition(glm::vec3(bFrontTwo->GetPosition().x, cameraPos.y - 1.3f, bFrontTwo->GetPosition().z));
	bMidTwo->SetPosition(glm::vec3(bMidTwo->GetPosition().x, cameraPos.y - 1.05f, bMidTwo->GetPosition().z));

	//! Keyboard controls:
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A))
	{
		//! Player moving left, background move right:
		movingRight = true;

		bFront->SetPosition(glm::vec3(bFront->GetPosition().x + (deltaTime_ / 2.0f), bFront->GetPosition().y, bFront->GetPosition().z));
		bMid->SetPosition(glm::vec3(bMid->GetPosition().x + (deltaTime_ / 4.0f), bMid->GetPosition().y, bMid->GetPosition().z));
		bFrontTwo->SetPosition(glm::vec3(bFrontTwo->GetPosition().x + (deltaTime_ / 2.0f), bFrontTwo->GetPosition().y, bFrontTwo->GetPosition().z));
		bMidTwo->SetPosition(glm::vec3(bMidTwo->GetPosition().x + (deltaTime_ / 4.0f), bMidTwo->GetPosition().y, bMidTwo->GetPosition().z));
	}

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D))
	{
		//! Player moving right, background move left:
		movingLeft = true;

		bFront->SetPosition(glm::vec3(bFront->GetPosition().x + (-deltaTime_ / 2.0f), bFront->GetPosition().y, bFront->GetPosition().z));
		bMid->SetPosition(glm::vec3(bMid->GetPosition().x + (-deltaTime_ / 4.0f), bMid->GetPosition().y, bMid->GetPosition().z));
		bFrontTwo->SetPosition(glm::vec3(bFrontTwo->GetPosition().x + (-deltaTime_ / 2.0f), bFrontTwo->GetPosition().y, bFrontTwo->GetPosition().z));
		bMidTwo->SetPosition(glm::vec3(bMidTwo->GetPosition().x + (-deltaTime_ / 4.0f), bMidTwo->GetPosition().y, bMidTwo->GetPosition().z));
	}


	//! Update centerpoints of all the objects:
	frontCenterOne = bFront->GetPosition().x +
		(bFront->GetModel()->GetBoundingBox().maxVert.x / 2);
	frontCenterTwo = bFrontTwo->GetPosition().x +
		(bFrontTwo->GetModel()->GetBoundingBox().maxVert.x / 2);

	midCenterOne = bMid->GetPosition().x +
		(bMid->GetModel()->GetBoundingBox().maxVert.x / 2);
	midCenterTwo = bMidTwo->GetPosition().x +
		(bMidTwo->GetModel()->GetBoundingBox().maxVert.x / 2);

	//! Check if centers of backgrounds are at the center of screen:
	if (movingRight)
	{
		//! Backgrounds are moving to the right:

		if (frontCenterOne >= backCenter)
		{
			//! Foreground is too far to the right, move ForegroundTwo's center to the center of the screen
			MoveLeft(bFront, bFrontTwo);
		}

		if (midCenterOne >= backCenter)
		{
			//! Background is too far to the right, move backgroundTwo's center to the center of the screen
			MoveLeft(bMid, bMidTwo);
		}
	}

	if (movingLeft)
	{
		//! Backgrounds moving left:
		if (backCenter >= frontCenterTwo)
		{
			//! Foreground is too far to the left, move ForegroundTwo's center to the center of the screen
			MoveRight(bFront, bFrontTwo);
		}

		if (backCenter >= midCenterTwo)
		{
			//! Background is too far to the right, move backgroundTwo's center to the center of the screen
			MoveRight(bMid, bMidTwo);
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

void ParallaxingBackground::Render(Camera* camera_)
{
	backgroundFront->Render(camera_);
	backgroundFrontTwo->Render(camera_);
	backgroundMid->Render(camera_);
	backgroundMidTwo->Render(camera_);
	backgroundBack->Render(camera_);
}