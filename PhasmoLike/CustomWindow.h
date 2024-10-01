#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "IManagable.h"

using namespace sf;
using namespace std;

class CustomWindow : public RenderWindow , public IManagable<string>
{
	Vector2i position;

public:
	Vector2i GetPercentPosition() const
	{
		return position;
	}

public:
	CustomWindow(const string& _id, const string& _titleName, const unsigned int _width, const unsigned int _height, const Vector2i& _screenPercentPosition);

private:
	void Register();
};

