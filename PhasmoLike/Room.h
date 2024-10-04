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
	BATHROOM
};

class Room : public Entity
{
	string levelStyle;
	RoomType roomType;

public:
	Room(const string& _style, const RoomType& _type);
};