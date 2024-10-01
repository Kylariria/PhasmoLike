#include "CustomWindow.h"
#include "WindowManager.h"
#include "WindowManager.h"

CustomWindow::CustomWindow(const string& _id, const string& _titleName, const unsigned int _width, const unsigned int _height, const Vector2i& _screenPercentPosition) : IManagable(_id)
{
	Register();
	create(sf::VideoMode(_width, _height), _titleName);
	position = _screenPercentPosition;
}

void CustomWindow::Register()
{
	WindowManager::GetInstance().Add(id,this);
}
