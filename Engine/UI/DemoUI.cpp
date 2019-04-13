#include "DemoUI.h"



DemoUI::DemoUI()
{
}


DemoUI::~DemoUI()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void DemoUI::Update(const float deltaTime_) {

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(w);
	ImGui::NewFrame();

	//setting the size and position of our window
	ImVec2 size = ImVec2(Engine::GetInstance()->GetScreenSize().x, Engine::GetInstance()->GetScreenSize().y);
	ImVec2 buttonSize = ImVec2(200, 100);
	ImVec2 pos = ImVec2(0, 0);
	ImGui::SetNextWindowSize(size);
	ImGui::SetNextWindowPos(pos);
	ImVec2 widgetPos = ImVec2(0, 0);

	//setting my preffered window flags
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoTitleBar;

	ImGui::Begin("Options", false, window_flags);

	ImGui::SetWindowFontScale(3.0f);

	static int audioV = 70;
	static int sfxV = 40;
	static int musicV = 10;
	Window* window = Engine::GetInstance()->GetWindow();

	ImVec2 titleSize = ImVec2(600, 200);

	//Sets the text for which state we are in, and shows the UI stuff when needed
	switch (demoState)
	{
	case 0:
		widgetPos = ImVec2(size.x / 2 - (titleSize.x / 2), 100);
		ImGui::SetCursorPos(widgetPos);
		ImGui::Image((void*)(intptr_t)titleImg, titleSize);
		break;
	case 1:
		//Audio Manager
		ImGui::Text("Audio Manager");
		break;
	case 2:
		//OBJ loader
		ImGui::Text("Obj Loader");
		break;
	case 3:
		//Input managers
		ImGui::Text("Input Managers");
		break;
	case 4:
		//Lighting
		ImGui::Text("Lighting");
		break;
	case 5:
		//Shader
		ImGui::Text("Shader");
		break;
	case 6:
		//Physics
		ImGui::Text("Physics");
		break;
	case 7:
		//Collision
		ImGui::Text("Collision");
		break;
	case 8:
		//UI
		ImGui::Text("UI");
		widgetPos = ImVec2(size.x / 2 - (buttonSize.x / 2), size.y / 2 - (buttonSize.y / 2));
		ImGui::SetCursorPos(widgetPos);
		ImGui::Button("UI Button", buttonSize);
		break;
	case 9:
		//Textures
		ImGui::Text("Textures");
		widgetPos = ImVec2(size.x / 2 - (buttonSize.x / 2), size.y / 2 - (buttonSize.y / 2));
		ImGui::SetCursorPos(widgetPos);
		ImGui::ImageButton((void*)(intptr_t)textureBtnImg, buttonSize);
		break;
	case 10:
		//Options
		ImGui::Text("Options");

		ImGui::SetWindowFontScale(1.0f);

		ImGui::Text("Audio");

		
		if (ImGui::SliderInt("Sounds / Voice Volume", &audioV, 0.0f, 100.0f))            // Edit 1 int using a slider from 0 to 100 to set Voice Audio
			AudioManager::GetInstance()->SetAudioVolume(0, audioV);

		
		if (ImGui::SliderInt("Sounds / SFX Volume", &sfxV, 0.0f, 100.0f))            // Edit 1 int using a slider from 0 to 100 to set SFX Audio
			AudioManager::GetInstance()->SetAudioVolume(1, sfxV);

		
		if (ImGui::SliderInt("Music", &musicV, 0.0f, 100.0f))            // Edit 1 int using a slider from 0 to 100 to set Music
			AudioManager::GetInstance()->SetMusicVolume(musicV);

		ImGui::Text("Window Settings");
		

		static bool isFullscreen;
		if (ImGui::Checkbox("Fullscreen", &isFullscreen)) {
			if (isFullscreen) {
				SDL_SetWindowFullscreen(w, SDL_WINDOW_FULLSCREEN);
			}
			else {
				SDL_SetWindowFullscreen(w, 0);
			}
		}

		if (ImGui::Button("1280x720", buttonSize)) {
			SDL_SetWindowSize(w, 1280, 720);
			glViewport(0, 0, 1280, 720);
			ImVec2 windowSize = ImVec2(1280, 720);
			ImGui::SetWindowSize(windowSize);
			window->SetHeight(720);
			window->SetWidth(1280);
		}

		if (ImGui::Button("1600x900", buttonSize)) {
			SDL_SetWindowSize(w, 1600, 900);
			glViewport(0, 0, 1600, 900);
			ImVec2 windowSize = ImVec2(1600, 900);
			ImGui::SetWindowSize(windowSize);
			window->SetHeight(900);
			window->SetWidth(1600);
		}

		if (ImGui::Button("1920x1080", buttonSize)) {
			SDL_SetWindowSize(w, 1920, 1080);
			glViewport(0, 0, 1920, 1080);
			ImVec2 windowSize = ImVec2(1920, 1080);
			ImGui::SetWindowSize(windowSize);
			window->SetHeight(1080);
			window->SetWidth(1920);
		}
		ImGui::SetWindowFontScale(3.0f);
		break;
	case 11:
		//Particles
		ImGui::Text("Particles");
		break;
	case 12:
		//Parallaxing Background
		ImGui::Text("Parallaxing Background");
		break;
	case 13:
		//AI & Enemies
		ImGui::Text("AI & Enemies");
		break;
	}

	//Credits
	ImGui::SetWindowFontScale(1.0f);
	widgetPos = ImVec2(size.x - size.x + 10.0f, size.y - 110.0f);
	ImGui::SetCursorPos(widgetPos);
	ImGui::Text("Credits: \n The Squire and The Squire Engine were created by: \n Matthew Troscianczuk: Project Owner, Programmer, 3D Modelling, Mechanics Design / Programming \n Jake G. Cunningham: SCRUM Master, Physics and General Programmer, AI / UI Designer \n Connor Wood: Programmer, Graphics Lead \n Grayson E. James: Audio Master \n Alexis Weltner: Writer");

	ImGui::End();

}