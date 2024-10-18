#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "IManager.h"
#include "Singleton.h"
#include "Menu.h"

#include "PathsMacro.h"
#include "CustomWindow.h"

class MenuManager : public Singleton<MenuManager>, public IManager<string, Menu>
{
	CustomWindow* window;
	sf::Vector2f factor;
	float* index;

public:
	std::vector<sf::Drawable*> GetDrawables();
	float* GetIndex();

public:
	MenuManager(); //1200 / 720 : main window size

public:
	void ClickAction();
	void Update();
	//bool BlockPlayer(); //TODO
	void InitMenu();
	//void OptionsMenu(); //TODO
	void CloseMenu();
	//void GraphicMenu(); //TODO
	void GameOverMenu();
	void Toggle();

private:
	void InitMenuPause();
	//void InitHUD(); //TODO
	//void InitMenuOptions(); //TODO
	void InitMenuClose();
	//void InitGraphicMenu();
	//void InitMenuLatency();
	void InitGameOver();
	//void Loading(); //TODO Maybe later
	void WarningSeizure();
	//void InitEpilepsyMenu(); //TODO
	//void InitCredits(); //TODO
	//void InitKeyboard(); //TODO
};

