#include "OptionsMenu.h"



OptionsMenu::OptionsMenu()
{
}


OptionsMenu::~OptionsMenu()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void OptionsMenu::Update(const float deltaTime_) {

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

	ImGui::Begin("Options", false, window_flags);

	widgetPos = ImVec2(0.0f, 23.0f);
	ImGui::SetCursorPos(widgetPos);
	if (ImGui::Button("Back", buttonSize)) {                           // This button brings up the options menu
		state = 1;
	}

	ImGui::Text("Audio");

	static int audioV = 70;
	if(ImGui::SliderInt("Sounds / Voice Volume", &audioV, 0.0f, 100.0f))            // Edit 1 int using a slider from 0.0f to 100.0f to set Audio
		AudioManager::GetInstance()->SetAudioVolume(0, audioV);

	static int musicV = 10;
	if (ImGui::SliderInt("Music", &musicV, 0.0f, 100.0f))            // Edit 1 float using a slider from 0.0f to 100.0f to set Audio
		AudioManager::GetInstance()->SetMusicVolume(musicV);

	ImGui::Text("Window Settings");
	Window* window = Engine::GetInstance()->GetWindow();

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

	if(ImGui::Button("1600x900", buttonSize)) {
		SDL_SetWindowSize(w, 1600, 900);
		glViewport(0, 0, 1600, 900);
		ImVec2 windowSize = ImVec2(1600, 900);
		ImGui::SetWindowSize(windowSize);
		window->SetHeight(900);
		window->SetWidth(1600);
	}

	if(ImGui::Button("1920x1080", buttonSize)) {
		SDL_SetWindowSize(w, 1920, 1080);
		glViewport(0, 0, 1920, 1080);
		ImVec2 windowSize = ImVec2(1920, 1080);
		ImGui::SetWindowSize(windowSize);
		window->SetHeight(1080);
		window->SetWidth(1920);
	}

	ImGui::End();

}