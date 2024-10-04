#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"	
#include "NetworkManager.h"
#include "WindowManager.h"
#include "TimerManager.h"
#include "Camera.h"

class Game
{
	WindowManager* windowManager = nullptr;
	CustomWindow* windowPtr = nullptr;
	NetworkManager* networkManager = nullptr;
	Camera* mainCamera = nullptr;
	bool isRunning = true;

	Player* player = nullptr;

	// Temp background test size
	Texture* _texture = nullptr;
	RectangleShape* _background = nullptr;

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
	//Manage events window
	void ManageWindow();
	//Draws on the window
	void Draw();
	void FollowPlayer();
public:
	//Tick
	void GameLoop();
};

