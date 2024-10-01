#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"	
#include "NetworkManager.h"
#include "WindowManager.h"

class Game
{
	WindowManager* windowManager = nullptr;
	CustomWindow* windowPtr = nullptr;
	NetworkManager* networkManager = nullptr;
	bool isRunning = true;

	Player* player = nullptr;

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

