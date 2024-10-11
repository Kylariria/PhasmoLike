#pragma once

#include <SFML\System\Vector2.hpp>

using namespace sf;

class IDirections
{
protected:
	int currentAngle;
	Vector2f forwardVector;
	Vector2f rightVector;

public:
	int GetCurrentDirection() const { return currentAngle; }
	Vector2f GetForwardVector() const { return forwardVector; }
	Vector2f GetRightVector() const { return rightVector; }

public:
	IDirections();

public:
	void virtual SetRotation(const int& _newDirection);
};