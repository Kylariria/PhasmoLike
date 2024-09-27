#include "WindowManager.h"
void WindowManager::InitMainWindow(const Vector2u& _size, const string& _name)
{
	mainWindow = new CustomWindow(_name);
	mainWindow->create(sf::VideoMode(_size.x, _size.y), _name);
}

void WindowManager::InitMainWindow(const unsigned int _width, const unsigned int _height, const string& _name)
{
	mainWindow = new CustomWindow(_name);
	mainWindow->create(sf::VideoMode(_width, _height), _name);
}
