#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../Core/Window.h"
#include "../Core/Engine.h"

class UIManager {

private:
	//Init Stuff
	ImGuiIO io;
	ImVec4 clear_color;
	SDL_GLContext c;

public:
	//This variable is for determining what state the UI is in, 0 for no UI, 1 for Main Menu, 2 for OptionsMenu (JakeCunningham)
	int state;

	SDL_Window* w;

	UIManager() {};
	virtual ~UIManager() {};

	//This bool is so that my menu's that are not the main menu don't run the new frame stuff twice when they get loaded
	bool firstTimeThrough;

	inline bool Initialize(SDL_Window* window_, SDL_GLContext context) {
		clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		//Setup Imgui Context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		state = 1;
		w = window_;
		c = context;

		ImGui_ImplSDL2_InitForOpenGL(w, c);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(w);
		ImGui::NewFrame();

		firstTimeThrough = true;

		return true;
	}

	virtual void Update(const float deltaTime_) = 0;

	inline void Render() {
		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
};

#endif // !UIMANAGER_H