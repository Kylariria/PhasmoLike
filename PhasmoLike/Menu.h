#pragma once
#include "IManagable.h"
#include "IManager.h"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class UIElements;
class Menu : public IManagable<string>, public IManager<string, UIElements>
{
	bool wantsToCloseMenu;
	bool isOpened;
	int zIndex;

public:
	int GetZIndex() const
	{
		return zIndex;
	}
	vector<UIElements*> GetElements() const
	{
		return GetAllValues();
	}
	bool IsOpened() const
	{
		return isOpened;
	}

public:
	Menu(const string& _id, const vector<UIElements*>&_elements, const int& _zIndex = 0, const bool& _isRelativeToCamera = false);

private:
	virtual void Register() override;

public:
	bool ClickAction();
	void Update(RenderWindow* _window);
	void Open();
	void Close();
	void Toggle();
	virtual vector<Drawable*> GetDrawables();
};

