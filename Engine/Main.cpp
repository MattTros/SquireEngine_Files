#include "Core/Engine.h"
#include "../Game/Game1.h"

int main(int argc, char* args[])
{
	Engine::GetInstance()->SetGameInterface(new Game1);

	Engine::GetInstance()->Initialize("Engine Window", 800, 600);
	Engine::GetInstance()->Run();

	return 0;
}