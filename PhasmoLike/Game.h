#pragma once
#include <SFML/Graphics.hpp>
#include "CustomWindow.h"
#include <iostream>

class Game
{
	CustomWindow* windowPtr = nullptr;
public:
	Game();
	~Game();
private:
	//Init
	void GeneralInit();
	void InitWindow();
	void InitBackground();
	//Manage events window
	void ManageWindow();
	//Draws on the window
	void Draw();
	void DrawUI();
	void DrawBackground();
public:
	//Tick
	void GameLoop();
};

