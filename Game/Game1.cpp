#include "Game1.h"

Game1::Game1()
{

}


Game1::~Game1()
{

}

bool Game1::Initialize()
{
	///Load Death Audio
	AudioManager::GetInstance()->LoadSoundFXFile("introAndWalkJumpTutorial", "Death_IntroAndWalkJumpTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("exposition", "Death_Exposition.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("dropDownTutorial", "Death_DropDownTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("attackTutorial", "Death_AttackTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("dashTutorial", "Death_DashTutorial.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("outro", "Death_Outro.wav");
	///Load SFX
	AudioManager::GetInstance()->LoadSoundFXFile("slash", "Sword_Slash.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("hit", "Sword_Hit.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("arrow", "Arrow_Shot.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("dash", "Dash_Sound.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("death", "Death_Sound.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("playerHit", "Player_Hit.wav");
	///Load Music
	AudioManager::GetInstance()->LoadMusicFile("backgroundMusic", "WaywardGhouls.wav");

	AudioManager::GetInstance()->SetAudioVolume(0, 70);
	AudioManager::GetInstance()->SetAudioVolume(1, 40);
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