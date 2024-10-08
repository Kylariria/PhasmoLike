#include "LevelGenerator.h"

LevelGenerator::LevelGenerator()
{
	settings = GeneratorSettings();
}
LevelGenerator::LevelGenerator(const GeneratorSettings& _settings)
{
	settings = _settings;
}

bool LevelGenerator::CheckValidity()
{
	if (!settings.IsValid()) return false;
	return true;
}
void LevelGenerator::GenerateRooms(int _number,const RoomType& _type)
{
	if (_number <= 0) return;
	while (_number >= 1)
	{
		Room* _room = nullptr;
		vector<Door> _doorsOnNewRoom;
		if (currentRoomAmount == 0)
		{
			_doorsOnNewRoom = GetDoors(basePath + GetPathByType(_type) + "/1.txt");
			_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, RoomRot::RR_RANDOM, Vector2f(0.0f, 0.0f));
		}
		else
		{
			// Get a random available door
			doorPositions;
			const Door& _door = GetRandomAvailableDoor();

			// Rotation
			_doorsOnNewRoom = GetDoors(basePath + GetPathByType(_type) + "/1.txt");
			const Door& _selectedDoor = _doorsOnNewRoom[RandomInRange(0, _doorsOnNewRoom.size() - 1)];
			cout << "Connecting corridor door direction " << _door.direction << " with " << _selectedDoor.direction << endl;
			int _rotation = GetRotation(_door, _selectedDoor);
			_rotation += _door.owner->GetRotation();
			RoomRot _rot = static_cast<RoomRot>((_rotation % 360) / 90);
			const int _roomRotation = NormalizeRotation(_door.direction + _door.owner->GetRotation());

			_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, _rot, Vector2f(0.0f, 0.0f));
			
			// Spawn position
			Vector2f _spawnPosition = _door.owner->GetSprite()->getPosition(); // Start at room location

			const Vector2u& _size = _door.owner->GetSprite()->getTexture()->getSize();
			if (_door.direction == 0) _spawnPosition.y -= _size.y / 2.0f; // Add half the door's room size
			else if (_door.direction == 90) _spawnPosition.x += _size.x / 2.0f; // Add half the door's room size
			else if (_door.direction == 180) _spawnPosition.y += _size.y / 2.0f; // Add half the door's room size
			else if (_door.direction == 270) _spawnPosition.x -= _size.x / 2.0f;  // Add half the door's room size

			const Vector2u& _newRoomSize = _room->GetSprite()->getTexture()->getSize();
			if (_door.direction == 0) _spawnPosition.y -= (_rot == RoomRot::RR_TOP || _rot == RoomRot::RR_BOTTOM) ? _newRoomSize.x / 2.0f :_newRoomSize.y / 2.0f; // Add half the door's room size
			else if (_door.direction == 90) _spawnPosition.x += (_rot == RoomRot::RR_TOP || _rot == RoomRot::RR_BOTTOM) ? _newRoomSize.x / 2.0f : _newRoomSize.y / 2.0f; // Add half the door's room size
			else if (_door.direction == 180) _spawnPosition.y += (_rot == RoomRot::RR_TOP || _rot == RoomRot::RR_BOTTOM) ? _newRoomSize.y / 2.0f : _newRoomSize.x / 2.0f; // Add half the door's room size
			else if (_door.direction == 270) _spawnPosition.x -= (_rot == RoomRot::RR_TOP || _rot == RoomRot::RR_BOTTOM) ? _newRoomSize.y / 2.0f : _newRoomSize.x / 2.0f;; // Add half the door's room size

			_room->SetPosition(_spawnPosition);

			// Remove _selectedDoor from _doorsOnNewRoom since it's used to connect to the other one
			_doorsOnNewRoom.erase(std::remove(_doorsOnNewRoom.begin(), _doorsOnNewRoom.end(), _selectedDoor), _doorsOnNewRoom.end());
		}
		_number--;
		currentRoomAmount++;
		cout << "--> Generated room: " << GetPathByType(_type) << endl;
		if (!_room) return;
		if (_doorsOnNewRoom.empty()) return;
		const int _size = static_cast<int>(_doorsOnNewRoom.size());
		for (int _index = 0; _index < _size; _index++)
		{
			_doorsOnNewRoom[_index].owner = _room;
			doorPositions.push_back(_doorsOnNewRoom[_index]);
		}
	}
}
string LevelGenerator::GetPathByType(const RoomType& _type)
{
	string _pathList[] = { "Bedrooms", "Kitchens", "Livingrooms", "Garages", "Corridors", "Bathrooms" };
	return _pathList[static_cast<int>(_type)];
}
Door LevelGenerator::GetRandomAvailableDoor()
{
	const int _size = static_cast<int>(doorPositions.size());
	if (_size == 0) return Door(0, 0, 0);
	const int _random = RandomInRange(0, _size - 1);
	const Door& _door = doorPositions[_random];
	doorPositions.erase(doorPositions.begin() + _random);
	return _door;
}
vector<Door> LevelGenerator::GetDoors(const string& _path)
{
	vector<Door> _doors;
	ifstream _stream = ifstream(_path);
	string _line;

	while (getline(_stream, _line))
	{
		if (_line[0] == '#') continue;

		string _posX = "";
		string _posY = "";
		string _direction = "";

		_posX = _line.substr(_line.find(':') + 2, _line.find('@'));
		_posY = _line.substr(_line.find('@') + 1, _line.size());
		_direction = _line.substr(0, _line.find(':'));

		_doors.push_back(Door(stoi(_posX), stoi(_posY), stoi(_direction)));
	}
	_stream.close();
	return _doors;
}
int LevelGenerator::GetRotation(const Door& _from, const Door& _to)
{
	if (_from.direction == 0) return 180;
	if (_from.direction == 90) return 270;
	if (_from.direction == 180) return 0;
	if (_from.direction == 270) return 90;
	return  0;
}
int LevelGenerator::RandomInRange(const int& _min, const int& _max)
{
	random_device _device;
	mt19937 _random(_device());
	uniform_int_distribution<mt19937::result_type> _distribution(_min, _max);
	return _distribution(_random);
}
int LevelGenerator::NormalizeRotation(int _value)
{
	while (_value >= 360) _value -= 360;
	return _value;
}
void LevelGenerator::Generate(const string& _levelStyle)
{
	if (!CheckValidity()) return;
	currentRoomAmount = 0;
	basePath = "Resources/Images/Maps/" + _levelStyle + "/";

	GenerateRooms(1, RoomType::CORRIDOR); // Starter corridor

	GenerateRooms(settings.bathrooms, RoomType::BATHROOM);
	GenerateRooms(settings.bedrooms, RoomType::BEDROOM);
	GenerateRooms(settings.corridors, RoomType::CORRIDOR);
	GenerateRooms(settings.garages, RoomType::GARAGE);
	GenerateRooms(settings.kitchens, RoomType::KITCHEN);
	GenerateRooms(settings.livingrooms, RoomType::LIVINGROOM);
}