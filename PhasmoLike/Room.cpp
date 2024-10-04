#include "Room.h"

Room::Room(const string& _id, const string& _path, const RoomType& _type, const RoomRot& _rot, const Vector2f& _pos) : Entity(_id, _pos,_path)
{

	roomType = _type;
	roomRot = _rot;
}
