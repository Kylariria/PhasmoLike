#include "Game.h"
#include "NetworkManager.h"

#include <chrono>
#include <thread>

Game::Game()
{

}

Game::~Game()
{

}

void Game::GeneralInit()
{
	InitManagers();
	InitWindow();
	windowManager->SetupAllPositions();
}

void Game::InitManagers()
{
	windowManager = &WindowManager::GetInstance();
}

void Game::InitWindow()
{
	windowPtr = windowManager->InitMainWindow(800, 600, "PhasmoLike");
	// Examples (TODO to move to correct places (ex: inv to an inventory class)
	new CustomWindow("inv", "Inventory", 300, 600, Vector2i(85, 50));
	new CustomWindow("emf", "EMF Reader", 300, 300, Vector2i(15, 25));
	new CustomWindow("journal", "Journal", 500, 300, Vector2i(15, 75));
}

void Game::ManageWindow()
{
	if (!isRunning) return;
	isRunning = !windowManager->CheckCloseEvent();
}

void Game::Draw()
{
	windowManager->DrawAll();
}

void Game::GameLoop()
{
	GeneralInit(); //First Init of all needed component and elements 

	while (isRunning) //Main Loop
	{
		ManageWindow(); //Check events related to the window;
		Draw(); //Main Draw function
		windowManager->TickAll();
		this_thread::sleep_for(chrono::milliseconds(50)); // TODO temporary, make TimerManager to avoid ticking that fast


		// TEMP
		if (!networkManager)
		{
			Event _event;
			while (windowPtr->pollEvent(_event))
			{
				if (_event.type == sf::Event::KeyPressed)
				{
					if (_event.key.code == sf::Keyboard::H)
					{
						// HOST
						networkManager = new NetworkManager(3000);
						networkManager->Start();
						networkManager->ListenForClients(1);
					}
					else if (_event.key.code == sf::Keyboard::C)
					{
						// CONNECT
						networkManager = new NetworkManager("ultired.redirectme.net", 3000);
						networkManager->Start();
					}
				}
			}
		}
	}

	if (networkManager) delete networkManager;

	windowManager->CloseAll();
}
