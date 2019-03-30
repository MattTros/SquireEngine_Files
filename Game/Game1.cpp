#include "Game1.h"

Game1::Game1()
{

}


Game1::~Game1()
{

}

bool Game1::Initialize()
{
	///Load Audio
	AudioManager::GetInstance()->LoadSoundFXFile("introAndWalkJumpTutorial", "Death_IntroAndWalkJumpTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("exposition", "Death_Exposition.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("dropDownTutorial", "Death_DropDownTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("attackTutorial", "Death_AttackTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("dashTutorial", "Death_DashTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("outro", "Death_Outro.wav");
	AudioManager::GetInstance()->LoadMusicFile("backgroundMusic", "WaywardGhouls.wav");

	AudioManager::GetInstance()->SetAudioVolume(0, 70);
	AudioManager::GetInstance()->SetMusicVolume(10);

	///Load Scenes
	SceneManager::GetInstance()->AddScene(new UIScene, 0);
	SceneManager::GetInstance()->AddScene(new Scene1, 1);
	SceneManager::GetInstance()->AddScene(new Scene2, 2);
	AudioManager::GetInstance()->PlayMusic("backgroundMusic");
	SceneManager::GetInstance()->SetScene(0);
	return true;
}

void Game1::Update(const float deltaTime_)
{
	SceneManager::GetInstance()->Update(deltaTime_);
	if (KeyboardInputManager::GetInstance()->KeyPressed(SDL_SCANCODE_ESCAPE))
		SceneManager::GetInstance()->SetScene(0);
}

void Game1::Render()
{
	SceneManager::GetInstance()->Render();
}