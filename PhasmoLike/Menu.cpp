#include "Menu.h"
#include "UIElements.h"
#include "UIButton.h"

Menu::Menu(const string& _id, const vector<UIElements*>& _elements, const int& _zIndex,
	const bool& _isRelativeToCamera) : IManagable(_id)
{
	wantsToCloseMenu = false;
	for (UIElements* _element : _elements)
	{
		_element->SetOwner(this);
		_element->Register();
	}
	zIndex = _zIndex;
	Register();
}

void Menu::Register()
{
}

bool Menu::ClickAction()
{
	for (UIElements* _element : GetAllValues())
	{
		UIButton* _button;
		if (_button = dynamic_cast<UIButton*>(_element))
		{
			if (_button->IsHover())
			{
				_button->ExecuteCallback();
				return true;
			}
		}
	}

	return false;
}

void Menu::Update(RenderWindow* _window)
{
	const Vector2i& _mousePosition = Mouse::getPosition(*_window);
	for (UIElements* _element : GetAllValues())
	{
		_element->Update(_mousePosition);
	}
	GarbageCollector();
}

void Menu::Open()
{
	isOpened = true;
}

void Menu::Close()
{
	isOpened = false;
}

void Menu::Toggle()
{
	isOpened = !isOpened;
}

vector<Drawable*> Menu::GetDrawables()
{
	vector<Drawable*> _drawables;
	for (UIElements* _element : GetAllValues())
	{
		vector<Drawable*> _elementDrawables = _element->GetDrawables();
		_drawables.insert(_drawables.end(), _elementDrawables.begin(), _elementDrawables.end());
	}
	return _drawables;
}
