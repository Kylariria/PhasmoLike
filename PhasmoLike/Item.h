#pragma once

#include <iostream>
#include <sfml/Graphics.hpp>

using namespace std;
using namespace sf;

class Item
{

protected:
	string name = "";
	Sprite* sprite = nullptr;

public:
	string GetName() const
	{
		return name;
	}
	Sprite* GetSprite() const
	{
		return sprite;
	}

public:
	Item();
	Item(const string& _name, const string& _path);
	~Item();

private:
	void Init(const string& _path);
};