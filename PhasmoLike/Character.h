#pragma once
#include "Entity.h"

class Character : public Entity
{


public:

	Character(const string& _name, const Vector2f& _position, const Vector2f& _size, const string& _path);
};

