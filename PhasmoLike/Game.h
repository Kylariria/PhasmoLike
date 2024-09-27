#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
protected :
	bool gameIsRunning = true;

	//TODO to change with the windowManager
	sf::RenderWindow window;
	sf::RenderWindow* windowPtr = nullptr;
	
	float width = 1200;
	float height = 800;

	std::string name = "PhasmoLike";

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

