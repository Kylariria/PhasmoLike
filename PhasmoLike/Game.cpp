#include "Game.h"
#include "NetworkManager.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "Action.h"
#include "CameraManager.h"

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
	networkInterface = NetworkInterface();
	InitManagers();
	InitWindow();
	InitBackground();
	InitCamera();
	windowManager->SetupAllPositions();
	player = new Player();
	windowPtr->AddDrawable(player->GetCharacter()->GetShape());

	// TODO temp
	new Action(ActionData("HostServer", [this]() { HostServer(); }, InputTypeData(ActionType::KeyReleased, Keyboard::H)), "Debugs");
	new Action(ActionData("JoinServer", [this]() { JoinServer(); }, InputTypeData(ActionType::KeyReleased, Keyboard::J)), "Debugs");
	new Action(ActionData("PingDebug", [this]() { if (networkManager) networkManager->SendData("DebugPing", ""); }, InputTypeData(ActionType::KeyReleased, Keyboard::M)), "Debugs");
}

void Game::InitManagers()
{
	windowManager = &WindowManager::GetInstance();
}

void Game::InitWindow()
{
	windowPtr = windowManager->InitMainWindow(1200, 720, "PhasmoLike");
	// Examples (TODO to move to correct places (ex: inv to an inventory class)
	//new CustomWindow("emf", "EMF Reader", 300, 300, Vector2i(15, 25));
	//new CustomWindow("journal", "Journal", 500, 300, Vector2i(15, 75));
}

void Game::InitCamera()
{
	mainCamera = CameraManager::GetInstance().InitMainCamera("Main",Vector2f(0.0f, 0.0f),Vector2f(200,200));
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
	FollowPlayer();
	windowPtr->setView(*mainCamera);
	windowManager->DrawAll();
	windowPtr->setView(windowPtr->getDefaultView());
}

void Game::FollowPlayer()
{
	mainCamera->setCenter(player->GetCharacter()->GetShape()->getPosition());
}

void Game::HostServer()
{
	if (networkManager) return;
	networkManager = new NetworkManager(3000);
	networkInterface.SetManager(networkManager);
	networkManager->Start();
	networkManager->ListenForClients(1);
}

void Game::JoinServer()
{
	if (networkManager) return;
	networkManager = new NetworkManager("IP HERE", 3000); // Change IP here!
	networkInterface.SetManager(networkManager);
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
		networkInterface.Tick();
	}

	windowManager->CloseAll();
}
