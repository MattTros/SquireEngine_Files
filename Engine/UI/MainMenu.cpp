#include "MainMenu.h"



MainMenu::MainMenu() {
	
}

MainMenu::~MainMenu() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void MainMenu::Update(const float deltaTime_) {

	// Start the Dear ImGui frame

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(w);
	ImGui::NewFrame();

	static int counter = 0;

	//setting the size and position of our window
	ImVec2 size = ImVec2(Engine::GetInstance()->GetScreenSize().x, Engine::GetInstance()->GetScreenSize().y);
	ImVec2 buttonSize = ImVec2(200, 100);
	ImVec2 titleSize = ImVec2(600, 200);
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

	ImGui::Begin("Main Menu", false, window_flags);

	widgetPos = ImVec2(size.x / 2 - (titleSize.x / 2), 100);
	ImGui::SetCursorPos(widgetPos);
	
	ImGui::Image((void*)(intptr_t)titleImg, titleSize);

	widgetPos = ImVec2(size.x / 2 - (buttonSize.x / 2), 100 + titleSize.y);
	ImGui::SetCursorPos(widgetPos);
	if (ImGui::ImageButton((void*)(intptr_t)newGameImg, buttonSize))
	{                      
		// This button will load the game scene without save data
		counter++;
		SceneManager::GetInstance()->SetScene(1);
	}

	widgetPos = ImVec2(size.x / 2 - (buttonSize.x / 2), 110 + buttonSize.y + titleSize.y);
	ImGui::SetCursorPos(widgetPos);
	if (ImGui::ImageButton((void*)(intptr_t)loadGameImg, buttonSize))
	{
		// This button will load the game scene with save data
		counter++;
		SceneManager::GetInstance()->SetScene(std::atoi(SaveManager::GetInstance()->LoadSave("save1").info.c_str()));
	}

	widgetPos = ImVec2(size.x / 2 - (buttonSize.x / 2), (110 * 2 )+ buttonSize.y + titleSize.y);
	ImGui::SetCursorPos(widgetPos);
	if (ImGui::ImageButton((void*)(intptr_t)optionsImg, buttonSize)) {                           // This button brings up the options menu
		state = 2;
	}
	
	widgetPos = ImVec2(size.x / 2 - (buttonSize.x / 2), (110 * 3) + buttonSize.y + titleSize.y);
	ImGui::SetCursorPos(widgetPos);
	if (ImGui::ImageButton((void*)(intptr_t)quitImg, buttonSize)) {                            // This button will quit
		SDL_Quit(); Engine::GetInstance()->ExitGame();
	}

	widgetPos = ImVec2(size.x - buttonSize.x - 20, size.y - buttonSize.y - 20);
	ImGui::SetCursorPos(widgetPos);
	if (ImGui::ImageButton((void*)(intptr_t)demoImg, buttonSize)) {                            // This button will load the demo
		SceneManager::GetInstance()->SetScene(3);
	}

	ImGui::End();

}


