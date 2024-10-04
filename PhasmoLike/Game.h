#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"	
#include "NetworkManager.h"
#include "WindowManager.h"
#include "TimerManager.h"

class Game
{
	WindowManager* windowManager = nullptr;
	CustomWindow* windowPtr = nullptr;
	NetworkManager* networkManager = nullptr;
	bool isRunning = true;

	Player* player = nullptr;

	// TODO Temp background test size
	Texture* texture = nullptr;
	RectangleShape* background = nullptr;

public:
	Game();
	~Game();
private:
	//Init
	void GeneralInit();
	void InitManagers();
	void InitWindow();
	void InitBackground();
	//Draws on the window
	void Draw();

	// TODO temp debug network
	void HostServer();
	void JoinServer();

public:
	//Tick
	void GameLoop();
};

