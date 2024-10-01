#include "CustomWindow.h"
#include "WindowManager.h"
#include "TextLibrary.h"

CustomWindow::CustomWindow(const string& _id, const string& _titleName, const unsigned int _width, const unsigned int _height, const Vector2i& _screenPercentPosition) : IManagable(_id)
{
	Register();
	defaultTitle = _titleName;
	create(sf::VideoMode(_width, _height), _titleName);
	position = _screenPercentPosition;
	hauntIndex = rand() % 40 + 20;
}

void CustomWindow::Register()
{
	WindowManager::GetInstance().Add(id,this);
}

void CustomWindow::Tick()
{
	string _hauntedWords[3] = { "DIE", "KILL", "BEHIND YOU" };
	if (isHaunted)
	{
		hauntIndex--;
		if (hauntIndex > 15)
		{
			setTitle(TextLibrary::HauntString(defaultTitle));
		}
		else
		{
			if (hauntIndex == 15)
			{
				setTitle(_hauntedWords[rand() % 3]);
			}
			if (hauntIndex <= 0)
			{
				hauntIndex = rand() % 50 + 20;
			}
		}
	}
}

void CustomWindow::Draw()
{
	clear();
	const int _size = static_cast<int>(drawables.size());
	for (int _index = 0; _index < _size; _index++)
	{
		draw(*drawables[_index]);
	}
	display();
}

void CustomWindow::AddDrawable(Drawable* _drawable)
{
	drawables.push_back(_drawable);
}