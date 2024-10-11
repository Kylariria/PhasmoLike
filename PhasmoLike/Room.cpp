#include "Room.h"
#include "Macro.h"

int Room::RandomInRange(const int& _min, const int& _max)
{
	random_device _device;
	mt19937 _random(_device());
	uniform_int_distribution<mt19937::result_type> _distribution(_min, _max);
	return _distribution(_random);
}

Room::Room(const string& _path, const RoomType& _type, const RoomRot& _rot, const Vector2f& _pos) : Entity(STRING_ID("Room"), _pos, _path)
{
	roomType = _type;
	roomRot = _rot;
	SetOriginAtMiddleSprite();
	if (roomRot == RoomRot::RR_RANDOM) SetRotation(RandomInRange(0, 3) * 90.0f);
	else SetRotation(static_cast<int>(roomRot) * 90.0f);
}

void Room::SetRotation(const int& _newDirection)
{
	IDirections::SetRotation(_newDirection);
	sprite->setRotation(_newDirection);
}