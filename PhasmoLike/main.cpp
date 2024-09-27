#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game _game;
	_game.GameLoop();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}