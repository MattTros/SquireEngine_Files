#include "Core/Engine.h"
#include "../Game/Game1.h"

int main(int argc, char* args[])
{
	Engine::GetInstance()->SetGameInterface(new Game1);

	Engine::GetInstance()->Initialize("The Squire", 1600, 900);
	Engine::GetInstance()->Run();

	return 0;
}