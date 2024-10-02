#include "Game.h"
#include "NetworkManager.h"
#include "EntityManager.h"
#include "CameraManager.h"
#include <chrono>
#include <thread>

Game::Game()
{

}

Game::~Game()
{
	delete _background;
	delete _texture;
}

void Game::GeneralInit()
{
	InitManagers();
	InitWindow();
	InitBackground();
	InitCamera();
	windowManager->SetupAllPositions();
	player = new Player();
	windowPtr->AddDrawable(player->GetCharacter()->GetShape());
}

void Game::InitManagers()
{
	windowManager = &WindowManager::GetInstance();
}

void Game::InitWindow()
{
	windowPtr = windowManager->InitMainWindow(800, 600, "PhasmoLike");
	// Examples (TODO to move to correct places (ex: inv to an inventory class)
	//new CustomWindow("inv", "Inventory", 300, 600, Vector2i(85, 50));
	//new CustomWindow("emf", "EMF Reader", 300, 300, Vector2i(15, 25));
	//new CustomWindow("journal", "Journal", 500, 300, Vector2i(15, 75));
}

void Game::InitCamera()
{
	mainCamera = CameraManager::GetInstance().InitMainCamera("Main",Vector2f(0.0f, 0.0f),Vector2f(200,200));
}

void Game::InitBackground()
{
	_texture = new Texture();
	if (!_texture->loadFromFile("Resources/Images/map1.png"))
	{
		return;
	}
	_background = new RectangleShape(Vector2f(1500.0f, 1500.0f));
	_background->setTexture(_texture);
	_background->setScale(800 / 1500.0f, 600 / 1500.0f);
	windowPtr->AddDrawable(_background);
}

void Game::ManageWindow()
{
	if (!isRunning) return;
	isRunning = !windowManager->CheckCloseEvent();
}

void Game::Draw()
{
	windowPtr->setView(*mainCamera);
	windowManager->DrawAll();
	windowPtr->setView(windowPtr->getDefaultView());
}

void Game::GameLoop()
{
	GeneralInit(); // First Init of all needed component and elements 

	TimerManager::GetInstance().SetRenderCallback([&]() { Draw(); });
	TimerManager::GetInstance().SetMaxFrameRate(60);
	
	while (isRunning) // Main Loop
	{
		ManageWindow(); // Check events related to the window;
		TimerManager::GetInstance().Update();
		EntityManager::GetInstance().UpdateAllEntities();
		windowManager->TickAll();


		// TEMP
		//if (!networkManager)
		//{
			Event _event;
			while (windowPtr->pollEvent(_event))
			{
				if (_event.type == sf::Event::KeyPressed)
				{
					/*if (_event.key.code == sf::Keyboard::H)
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
					}*/
				}
				else if(_event.type == sf::Event::MouseButtonPressed)
				{
					if (_event.mouseButton.button == Mouse::Left)
					{
						cout << "Set new location" << endl;
						const Vector2i _mousePos = Mouse::getPosition(*windowPtr);
						player->SetNewCharacterLocTarget(windowPtr->mapPixelToCoords(_mousePos));
					}
				}
				
			}
		/* }
		if (networkManager)
		{
			networkManager->Tick();
		}*/
	}

	if (networkManager) delete networkManager;

	windowManager->CloseAll();
}
