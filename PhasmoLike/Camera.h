#pragma once
#include "IManagable.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

using namespace sf;


class Camera : public IManagable<string> , public View
{
public:
	Camera(const string& _id, const Vector2f& _position, const Vector2f& _size);

public:
	virtual void Register() override;
};

