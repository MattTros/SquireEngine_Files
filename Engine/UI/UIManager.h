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
	
	ImVec4 clear_color;
	

public:
	//This variable is for determining what state the UI is in, 0 for no UI, 1 for Main Menu, 2 for OptionsMenu (JakeCunningham)
	int state;

	ImGuiIO io;
	SDL_Window* w;
	SDL_GLContext c;

	UIManager() {};
	virtual ~UIManager() {};

	GLuint heart1;
	GLuint heart2;
	GLuint heart3;

	GLuint newGameImg;
	GLuint loadGameImg;
	GLuint optionsImg;
	GLuint quitImg;
	GLuint demoImg;
	GLuint titleImg;

	inline bool Initialize(SDL_Window* window_, SDL_GLContext context) {

		clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		//Textures
		std::string texturePath = "Resources/Textures/";
		TextureHandler::GetInstance()->CreateTexture("heart", texturePath + "HealthHeart.png");
		TextureHandler::GetInstance()->CreateTexture("brokenHeart", texturePath + "LostHeart.png");

		///Buttons & Title
		TextureHandler::GetInstance()->CreateTexture("newGame", texturePath + "NewGameButton.png");
		TextureHandler::GetInstance()->CreateTexture("loadGame", texturePath + "LoadGameButton.png");
		TextureHandler::GetInstance()->CreateTexture("options", texturePath + "OptionsButton.png");
		TextureHandler::GetInstance()->CreateTexture("quit", texturePath + "QuitButton.png");
		TextureHandler::GetInstance()->CreateTexture("demo", texturePath + "DemoButton.png");
		TextureHandler::GetInstance()->CreateTexture("title", texturePath + "Title.png");

		newGameImg = TextureHandler::GetInstance()->GetTexture("newGame");
		loadGameImg = TextureHandler::GetInstance()->GetTexture("loadGame");
		optionsImg = TextureHandler::GetInstance()->GetTexture("options");
		quitImg = TextureHandler::GetInstance()->GetTexture("quit");
		demoImg = TextureHandler::GetInstance()->GetTexture("demo");
		titleImg = TextureHandler::GetInstance()->GetTexture("title");

		heart1 = TextureHandler::GetInstance()->GetTexture("heart");
		heart2 = TextureHandler::GetInstance()->GetTexture("heart");
		heart3 = TextureHandler::GetInstance()->GetTexture("heart");

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

		return true;
	}

	virtual void Update(const float deltaTime_) = 0;

	inline void Render() {
		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	inline void SetTag(std::string tag_) {
		tag = tag_;
	}

	inline std::string GetTag() {
		return tag;
	}

private:
	std::string tag;
};

#endif // !UIMANAGER_H