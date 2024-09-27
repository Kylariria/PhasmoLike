#include "Game.h"

Game::Game()
{
}

Game::~Game()
{

}

void Game::GeneralInit()
{
	InitWindow();
	InitBackground();
}

void Game::InitWindow()
{
	window.create(sf::VideoMode(width, height), name);
	windowPtr = &window;
}

void Game::ManageWindow()
{
	if (!windowPtr) return;
	if (windowPtr->isOpen())
	{
		sf::Event _event;
		while (windowPtr->pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
			{
				windowPtr->close();
				gameIsRunning = false;
			}
		}
	}
}

void Game::Draw()
{
}

void Game::DrawUI()
{
}

void Game::DrawBackground()
{
}

void Game::InitBackground()
{
}

void Game::GameLoop()
{
	GeneralInit(); //First Init of all needed component and elements 

	while (gameIsRunning) //Main Loop
	{
		ManageWindow(); //Check events related to the window;
		Draw(); //Main Draw function
	}
}
