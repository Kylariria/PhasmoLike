#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "IManagable.h"

using namespace sf;
using namespace std;

class CustomWindow : public RenderWindow , public IManagable<string>
{
	string defaultTitle;
	Vector2i position;
	bool isHaunted;
	int hauntIndex;
	vector<Drawable*> drawables;
	bool isHidden;

public:
	bool IsHidden() const
	{
		return isHidden;
	}
	void SetHidden(const bool _newHidden);
	Vector2i GetPercentPosition() const
	{
		return position;
	}
	void SetHaunted(const bool _newHaunted)
	{
		isHaunted = _newHaunted;
		if (!isHaunted) setTitle(defaultTitle);
	}

public:
	CustomWindow(const string& _id, const string& _titleName, const unsigned int _width, const unsigned int _height, const Vector2i& _screenPercentPosition, const bool _isHiddenByDefault);

private:
	void Register();

public:
	void Tick();
	void Draw();
	void AddDrawable(Drawable* _drawable);
};

