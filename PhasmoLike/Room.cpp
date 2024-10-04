#include "Room.h"

Room::Room(const string& _style, const RoomType& _type) : Entity("Room", Vector2f(0.0f, 0.0f), 0.0f, "")
{
	levelStyle = _style;
	roomType = _type;
}
