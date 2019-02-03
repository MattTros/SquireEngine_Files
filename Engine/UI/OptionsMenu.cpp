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
	if (!firstTimeThrough) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(w);
		ImGui::NewFrame();
		
	}
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

	ImGui::Begin("Main Menu", false, window_flags);

	widgetPos = ImVec2(0.0f, 23.0f);
	ImGui::SetCursorPos(widgetPos);
	if (ImGui::Button("Back", buttonSize)) {                           // This button brings up the options menu
		state = 1;
	}

	float f = 200.0f;
	ImGui::SliderFloat("Audio", &f, 0.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 100.0f to set Audio

	ImGui::End();

	if (firstTimeThrough) {
		firstTimeThrough = false;
	}

	//tutorial stuff
	//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	////ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	////ImGui::Checkbox("Another Window", &show_another_window);

	//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//	counter++;
	//ImGui::SameLine();
	//ImGui::Text("counter = %d", counter);

	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//ImGui::End();

}