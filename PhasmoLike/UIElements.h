#pragma once
#include "IManagable.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Menu;
class UIElements : public IManagable<string>
{
	Vector2f position;
	Menu* owner = nullptr;

public:
	void SetOwner(Menu* _owner)
	{
		owner = _owner;
	}

public:
	UIElements();
	UIElements(const string& _id, const Vector2f& _position);

public:
	virtual void Update(const Vector2i& _mousePosition) = 0;
	virtual vector<Drawable*> GetDrawables() = 0;
	virtual void Register() override;
};

