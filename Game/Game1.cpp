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
	///Load Demo Audio
	AudioManager::GetInstance()->LoadSoundFXFile("demoIntro", "Demo_Intro.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoAudio", "Demo_AudioManager.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoOBJLoader", "Demo_ObjLoader.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoInput", "Demo_InputManagers.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoLighting", "Demo_Lighting.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoShader", "Demo_Shader.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoPhysics", "Demo_Physics.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoCollision", "Demo_Collision.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoUI", "Demo_UI.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoTextures", "Demo_Textures.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoOptions", "Demo_Options.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoParticles", "Demo_Particles.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoParallaxingBG", "Demo_ParallaxingBackground.wav");
	AudioManager::GetInstance()->LoadSoundFXFile("demoAI", "Demo_AIEnemies.wav");

	///Default Audio Levels
	AudioManager::GetInstance()->SetAudioVolume(0, 70);
	AudioManager::GetInstance()->SetAudioVolume(1, 40);
	AudioManager::GetInstance()->SetMusicVolume(10);

	///Load Scenes
	SceneManager::GetInstance()->AddScene(new UIScene, 0);
	SceneManager::GetInstance()->AddScene(new Scene1, 1);
	SceneManager::GetInstance()->AddScene(new Scene2, 2);
	SceneManager::GetInstance()->AddScene(new DemoScene, 3);
	AudioManager::GetInstance()->PlayMusic("backgroundMusic");
	SceneManager::GetInstance()->SetScene(0);

	return true;
}

void Game1::Update(const float deltaTime_)
{
	SceneManager::GetInstance()->Update(deltaTime_);
	if (KeyboardInputManager::GetInstance()->KeyPressed(SDL_SCANCODE_ESCAPE) && SceneManager::GetInstance()->GetSceneIndex() != 0)
	{
		if(SceneManager::GetInstance()->GetSceneIndex() == 3)
			AudioManager::GetInstance()->PlayMusic("backgroundMusic", -1);
		Camera::GetInstance()->GetLightSources().at(0)->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
		AudioManager::GetInstance()->StopAudioChannel(0);
		AudioManager::GetInstance()->StopAudioChannel(1);
		if (SaveManager::GetInstance()->CheckExists("save1"))
		{
			Save saveData = Save();
			saveData.name = "save1";
			saveData.info = std::to_string(SceneManager::GetInstance()->GetSceneIndex());
			SaveManager::GetInstance()->WriteTo(saveData);
		}
		else
		{
			Save saveData = Save();
			saveData.name = "save1";
			saveData.info = std::to_string(SceneManager::GetInstance()->GetSceneIndex());
			SaveManager::GetInstance()->CreateSave("save1", saveData);
		}
		SceneManager::GetInstance()->SetScene(0);
	}
}

void Game1::Render()
{
	SceneManager::GetInstance()->Render();
}