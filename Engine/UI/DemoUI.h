#ifndef DEMO_UI_H
#define DEMO_UI_H

#include "../UI/UIManager.h" 
#include "../FX/AudioManager.h"

class DemoUI : public UIManager {

public:
	DemoUI();
	~DemoUI();

	void Update(const float deltaTime_);

	int demoState = 0;

};

#endif // DEMU_UI_H
