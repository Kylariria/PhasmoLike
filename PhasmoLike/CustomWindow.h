#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "IManagable.h"

using namespace sf;
using namespace std;

class CustomWindow : public RenderWindow , public IManagable<string>
{
public:
	CustomWindow(const string& _name);

private:
	void Register();
};

