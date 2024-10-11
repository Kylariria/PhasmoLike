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
	delete player;
	if (networkManager) delete networkManager;
	delete levelGenerator;
}

void Game::GeneralInit()
{
	networkManager = new NetworkManager();
	networkManager->SetConfigDebugsMessages(true);
	InitManagers();
	InitWindow();
	InitBackground();
	InitCamera();
	windowManager->SetupAllPositions();
	player = new Player();


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
	mainCamera = CameraManager::GetInstance().InitMainCamera("Main",Vector2f(0.0f, 0.0f),Vector2f(333*1.8f,200*1.8f));
}

void Game::InitBackground()
{
	levelGenerator = new LevelGenerator(GeneratorSettings(0, 0, 4, 0, 0, 0));
	levelGenerator->Generate("Classic");
	windowPtr->AddDrawable(levelGenerator->debugCenterRoom);
	windowPtr->AddDrawable(levelGenerator->debugDoorRoom);
	windowPtr->AddDrawable(levelGenerator->debugOriginRoom);
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
	networkManager->StartServer(3000);
	networkManager->StartListen();
}

void Game::JoinServer()
{
	networkManager->StartClient("localhost" /*"192.168.10.59"*/, 3000);
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
	}

	windowManager->CloseAll();
}
