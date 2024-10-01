#include "WindowManager.h"

WindowManager::WindowManager()
{
	InitScreenSize();
}

void WindowManager::InitScreenSize()
{
	Vector2u _screenSize = Vector2u(0, 0);
	_screenSize.x = sf::VideoMode::getDesktopMode().width;
	_screenSize.y = sf::VideoMode::getDesktopMode().height;
	screenSize = _screenSize;
}

CustomWindow* WindowManager::InitMainWindow(const Vector2u& _size, const string& _name)
{
	mainWindow = new CustomWindow("main", _name, _size.x, _size.y, Vector2i(50, 50));
	return mainWindow;
}

CustomWindow* WindowManager::InitMainWindow(const unsigned int _width, const unsigned int _height, const string& _name)
{
	mainWindow = new CustomWindow("main", _name, _width, _height, Vector2i(50, 50));
	return mainWindow;
}

void WindowManager::CloseAll()
{
	for (const auto& _pair : allValues)
	{
		CustomWindow* _window = _pair.second;
		if (!_window) continue;
		_window->close();
	}
}

bool WindowManager::CheckCloseEvent()
{
	for (const auto& _pair : allValues)
	{
		CustomWindow* _window = _pair.second;
		if (!_window) continue;
		Event _event;
		while (_window->pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
			{
				return true;
			}
		}
	}
	return false;
}

void WindowManager::SetupPosition(CustomWindow* _window)
{
	Vector2i _screenPercent = _window->GetPercentPosition();
	Vector2i _targetPosition = Vector2i(static_cast<int>((_screenPercent.x / 100.0f) * screenSize.x), static_cast<int>((_screenPercent.y / 100.0f) * screenSize.y));
	// Adding origin offset
	_targetPosition.x -= _window->getSize().x / 2;
	_targetPosition.y -= _window->getSize().y / 2;
	// Updating window position
	_window->setPosition(_targetPosition);
	cout << "Init position: " << _window->GetID() << endl;
}

void WindowManager::SetupAllPositions()
{
	for (const auto& _pair : allValues)
	{
		CustomWindow* _window = _pair.second;
		if (!_window) continue;
		SetupPosition(_window);
	}
}
void WindowManager::DrawAll()
{
	for (const auto& _pair : allValues)
	{
		CustomWindow* _window = _pair.second;
		if (!_window) continue;
		_window->Draw();
	}
}

void WindowManager::TickAll()
{
	for (const auto& _pair : allValues)
	{
		CustomWindow* _window = _pair.second;
		if (!_window) continue;
		_window->Tick();
	}
}