#pragma once

#include <iostream>

#include "Entity.h"

using namespace std;

enum class RoomType
{
	BEDROOM,
	KITCHEN,
	LIVINGROOM,
	GARAGE,
	CORRIDOR,
	BATHROOM,
};

enum class RoomRot
{
	RR_TOP,
	RR_BOTTOM,
	RR_LEFT,
	RR_RIGHT
};


class Room : public Entity
{
	RoomType roomType;
	RoomRot roomRot;

public:
	Room(const string& _id, const string& _path, const RoomType& _type, const RoomRot& _rot, const Vector2f& _pos);
};