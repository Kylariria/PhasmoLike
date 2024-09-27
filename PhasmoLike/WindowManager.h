#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "CustomWindow.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class WindowManager : public Singleton<WindowManager> , public IManager<string,CustomWindow>
{
	CustomWindow* mainWindow = nullptr;
public:
	void InitMainWindow(const Vector2u& _size, const string& _name);
	void InitMainWindow(const unsigned int _width, const unsigned int _height, const string& _name);

};

