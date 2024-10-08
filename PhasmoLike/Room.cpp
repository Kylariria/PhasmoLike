#include "Room.h"
#include "Macro.h"

Room::Room(const string& _path, const RoomType& _type, const RoomRot& _rot, const Vector2f& _pos) : Entity(STRING_ID("Room"), _pos, _path)
{
	roomType = _type;
	roomRot = _rot;
	SetOriginAtMiddleSprite();
}
