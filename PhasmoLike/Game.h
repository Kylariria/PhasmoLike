#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "WindowManager.h"

class Game
{
	WindowManager* windowManager = nullptr;
	CustomWindow* windowPtr = nullptr;
	bool isRunning = true;

public:
	Game();
	~Game();
private:
	//Init
	void GeneralInit();
	void InitManagers();
	void InitWindow();
	//Manage events window
	void ManageWindow();
	//Draws on the window
	void Draw();
public:
	//Tick
	void GameLoop();
};

