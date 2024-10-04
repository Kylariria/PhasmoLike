#include "Game.h"
#include "NetworkManager.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "Action.h"

Game::Game()
{

}

Game::~Game()
{
	delete background;
	delete texture;
	delete player;
	if (networkManager) delete networkManager;
}

void Game::GeneralInit()
{
	InitManagers();
	InitWindow();
	InitBackground();
	windowManager->SetupAllPositions();
	player = new Player();
	windowPtr->AddDrawable(player->GetCharacter()->GetShape());

	// TODO temp
	new Action(ActionData("HostServer", [this]() { HostServer(); }, InputTypeData(ActionType::KeyReleased, Keyboard::H)), "Debugs");
	new Action(ActionData("JoinServer", [this]() { JoinServer(); }, InputTypeData(ActionType::KeyReleased, Keyboard::J)), "Debugs");
}

void Game::InitManagers()
{
	windowManager = &WindowManager::GetInstance();
}

void Game::InitWindow()
{
	windowPtr = windowManager->InitMainWindow(800, 600, "PhasmoLike");
	// Examples (TODO to move to correct places (ex: inv to an inventory class)
	//new CustomWindow("emf", "EMF Reader", 300, 300, Vector2i(15, 25));
	//new CustomWindow("journal", "Journal", 500, 300, Vector2i(15, 75));
}

void Game::InitBackground()
{
	texture = new Texture();
	if (!texture->loadFromFile("Resources/Images/map1.png"))
	{
		return;
	}
	background = new RectangleShape(Vector2f(1500.0f, 1500.0f));
	background->setTexture(texture);
	background->setScale(800 / 1500.0f, 600 / 1500.0f);
	windowPtr->AddDrawable(background);
}

void Game::Draw()
{
	windowManager->DrawAll();
}

void Game::HostServer()
{
	if (networkManager) return;
	networkManager = new NetworkManager(3000);
	networkManager->Start();
	networkManager->ListenForClients(1);
}

void Game::JoinServer()
{
	if (networkManager) return;
	networkManager = new NetworkManager("IP HERE", 3000); // Change IP here!
	networkManager->Start();
}

void Game::GameLoop()
{
	GeneralInit(); // First Init of all needed component and elements 

	TimerManager::GetInstance().SetRenderCallback([&]() { Draw(); });
	TimerManager::GetInstance().SetMaxFrameRate(60);

	while (isRunning) // Main Loop
	{
		TimerManager::GetInstance().Update();
		EntityManager::GetInstance().UpdateAllEntities();
		windowManager->TickAll();
		if (!InputManager::GetInstance().Update()) isRunning = false;
		if (networkManager) networkManager->Tick();
	}

	windowManager->CloseAll();
}
