#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "CustomWindow.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class WindowManager : public Singleton<WindowManager> , public IManager<string,CustomWindow>
{
	CustomWindow* mainWindow = nullptr;
	Vector2u screenSize;

public:
	Vector2u GetScreenSize() const
	{
		return screenSize;
	}

public:
	CustomWindow* GetMainWindow() const
	{
		return mainWindow;
	}

public:
	WindowManager();

private:
	void InitScreenSize();
	void SetupPosition(CustomWindow* _window);

public:
	CustomWindow* InitMainWindow(const Vector2u& _size, const string& _name);
	CustomWindow* InitMainWindow(const unsigned int _width, const unsigned int _height, const string& _name);
	void CloseAll();
	bool CheckCloseEvent();
	void SetupAllPositions();
	void DrawAll();
	void TickAll();
};

