#pragma once

#include <iostream>
#include "Macro.h"
#include "Entity.h"
#include "IDirections.h".h"

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
	RR_RIGHT,
	RR_BOTTOM,
	RR_LEFT,
	RR_RANDOM,
};


class Room : public Entity, public IDirections
{
	RoomType roomType;
	RoomRot roomRot;

public:
	float GetRotationWithType(const RoomRot& _type) const
	{
		vector<float> _rots = { 0.0f, 90.0f, 180.0f, 270.0f };
		const int _randIndex = Random(0, 3);

		const int& _value = _type == RoomRot::RR_RANDOM ? _randIndex : int(_type);
		return _rots[_value];
	}

private:
	int RandomInRange(const int& _min, const int& _max);

public:
	Room(const string& _path, const RoomType& _type, const RoomRot& _rot, const Vector2f& _pos);

public:
	virtual void SetRotation(const int& _newDirection) override;
};