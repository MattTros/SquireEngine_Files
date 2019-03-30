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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(w);
	ImGui::NewFrame();

	//setting the size and position of our window
	ImVec2 size = ImVec2(Engine::GetInstance()->GetScreenSize().x, Engine::GetInstance()->GetScreenSize().y);
	ImVec2 imgSize = ImVec2(100, 100);
	ImVec2 textSize = ImVec2(200, 100);
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

	//Tutorial popups

	//show the correct Tutorial info based on the tag from the TutorialCollider class
	ImGui::SetWindowFontScale(3.0f);
	if (GetTag() == "Jump") {
		ImGui::Text("Press Space to jump");
	}
	else if (GetTag() == "Movement") {
		ImGui::Text("Press A to move left and D to move right");
	}
	else if (GetTag() == "Exposition")
	{
		ImGui::Text("");
		if (!expositionAudioPlayed)
			AudioManager::GetInstance()->PlaySoundFX("exposition");
		expositionAudioPlayed = true;
	}
	else if (GetTag() == "Drop") {
		ImGui::Text("Press S to drop through platforms that look like this one!");
		if(!dropDownAudioPlayed)
			AudioManager::GetInstance()->PlaySoundFX("dropDownTutorial");
		dropDownAudioPlayed = true;
	}
	else if (GetTag() == "Dash") {
		ImGui::Text("Press LShift to dash");
		if(!dashAudioPlayed)
			AudioManager::GetInstance()->PlaySoundFX("dashTutorial");
		dashAudioPlayed = true;
	}
	else if (GetTag() == "SwordAttack") {
		ImGui::Text("Press left or right arrow to swing your sword");
		if(!attackAudioPlayed)
			AudioManager::GetInstance()->PlaySoundFX("attackTutorial");
		attackAudioPlayed = true;
	}
	else if (GetTag() == "Arrow") {
		ImGui::Text("Press F to fire an arrow");
	}
	else {

	}

	ImGui::End();
}