#ifndef MAINMENU_H
#define MAINMENU_H

#include "../UI/UIManager.h" 

class MainMenu : public UIManager{

public:
	MainMenu();
	~MainMenu();

	void Update(const float deltaTime_);

};

#endif // MAINMENU_H