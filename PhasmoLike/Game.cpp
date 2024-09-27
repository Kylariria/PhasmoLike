#include "Game.h"
#include "WindowManager.h"

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
	WindowManager::GetInstance().InitMainWindow(800, 600, "Main");
	windowPtr = WindowManager::GetInstance().Get("Main");
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
				
			}
		}
	}
}

void Game::Draw()
{
	DrawBackground();
	DrawUI();
}

void Game::DrawUI()
{
	windowPtr->clear();

	windowPtr->display();
}

void Game::DrawBackground()
{
	windowPtr->clear();

	windowPtr->display();
}

void Game::InitBackground()
{
}

void Game::GameLoop()
{
	GeneralInit(); //First Init of all needed component and elements 

	while (windowPtr->isOpen()) //Main Loop
	{
		ManageWindow(); //Check events related to the window;
		Draw(); //Main Draw function
	}
}
