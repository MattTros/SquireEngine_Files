#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "../UI/UIManager.h" 
#include "../FX/AudioManager.h"

class OptionsMenu : public UIManager {

public:
	OptionsMenu();
	~OptionsMenu();

	void Update(const float deltaTime_);

};

#endif // OPTIONSMENU_H