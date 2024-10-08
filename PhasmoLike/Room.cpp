#include "Room.h"
#include "Macro.h"

void Room::UpdateRotation()
{
	if (roomRot == RoomRot::RR_RANDOM)
	{
		sprite->setRotation(RandomInRange(0, 3) * 90.0f);
		return;
	}
	sprite->setRotation(static_cast<int>(roomRot) * 90.0f);
}

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
	UpdateRotation();
}

int Room::GetRotation()
{
	if (!sprite) return 0;
	return sprite->getRotation();
}
