#include <iostream>
#include "Game.h"

int WinMain()
{
	Game game;
	game.run();
	game.~Game();
	return 0;
}