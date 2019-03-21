#include "PlayerUI.h"

PlayerUI::PlayerUI() {

}

PlayerUI::~PlayerUI() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void PlayerUI::Update(const float deltaTime_) {
	// Start the Dear ImGui frame
	if (!firstTimeThrough) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(w);
		ImGui::NewFrame();
	}

	//setting the size and position of our window
	ImVec2 size = ImVec2(Engine::GetInstance()->GetScreenSize().x, Engine::GetInstance()->GetScreenSize().y);
	ImVec2 imgSize = ImVec2(100, 100);
	ImVec2 pos = ImVec2(0, 0);
	ImGui::SetNextWindowSize(size);
	ImGui::SetNextWindowPos(pos);
	ImVec2 widgetPos = ImVec2(0, 0);

	//setting my preffered window flags
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoInputs;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoTitleBar;

	ImGui::Begin("HUD", false, window_flags);

	widgetPos = ImVec2(10.0f, 10.0f);
	ImGui::SetCursorPos(widgetPos);
	ImGui::Image((void*)(intptr_t)heart1, imgSize);

	widgetPos = ImVec2(120.0f, 10.0f);
	ImGui::SetCursorPos(widgetPos);
	ImGui::Image((void*)(intptr_t)heart2, imgSize);

	widgetPos = ImVec2(230.0f, 10.0f);
	ImGui::SetCursorPos(widgetPos);
	ImGui::Image((void*)(intptr_t)heart3, imgSize);

	ImGui::End();

	if (firstTimeThrough) {
		firstTimeThrough = false;
	}
}


