#ifndef PLAYER_UI
#define PLAYER_UI

#include "../UI/UIManager.h" 
#include "../../Game/Scenes/SceneManager.h"
#include "../../Game/GameObjects/Player.h"

class PlayerUI : public UIManager {

public:
	PlayerUI();
	~PlayerUI();

	void Update(const float deltaTime_);
private:
	bool dropDownAudioPlayed = false;
	bool dashAudioPlayed = false;
	bool attackAudioPlayed = false;
	bool expositionAudioPlayed = false;
};

#endif // !PLAYER_UI