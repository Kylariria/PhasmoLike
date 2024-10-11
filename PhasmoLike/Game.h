#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"	
#include "NetworkInterface.h"
#include "WindowManager.h"
#include "TimerManager.h"
#include "Camera.h"
#include "LevelGenerator.h"

#include <thread>

class Game
{
	WindowManager* windowManager = nullptr;
	CustomWindow* windowPtr = nullptr;
	NetworkManager* networkManager = nullptr;
	Camera* mainCamera = nullptr;
	bool isRunning = true;
	LevelGenerator* levelGenerator = nullptr;

	Player* player = nullptr;

public:
	Game();
	~Game();
private:
	//Init
	void GeneralInit();
	void InitManagers();
	void InitWindow();

	void InitCamera();
	void InitBackground();
	//Draws on the window
	void Draw();
	void FollowPlayer();
	// TODO temp debug network
	void HostServer();
	void JoinServer();

public:
	//Tick
	void GameLoop();
};

