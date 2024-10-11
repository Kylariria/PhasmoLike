#include "LevelGenerator.h"
#include "WindowManager.h"

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
			_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, RoomRot::RR_RIGHT, Vector2f(0.0f, 0.0f));
		}
		else
		{
			const Door& _doorFirstRoom = GetRandomAvailableDoor();
			_doorsOnNewRoom = GetDoors(basePath + GetPathByType(_type) + "/1.txt");
			const Door& _selectedDoor = _doorsOnNewRoom[RandomInRange(0, _doorsOnNewRoom.size() - 1)];

			Vector2f _posRedPixelFirstRoom = _doorFirstRoom.GetPosition();
			Vector2f _firstRoomPos = _doorFirstRoom.owner->GetSprite()->getPosition();
			Vector2f _baseOriginFirstRoomPos = _firstRoomPos - (Vector2f(_doorFirstRoom.owner->GetSprite()->getTexture()->getSize()) / 2.0f);
			Vector2f _redPixelFirstRoomPosBasedOnLevelCenter = FixRedPosition(_baseOriginFirstRoomPos + _posRedPixelFirstRoom, _doorFirstRoom.owner->GetRotation());

			int _rotation = GetRotation(_doorFirstRoom, _selectedDoor);
			_rotation += _doorFirstRoom.owner->GetRotation();
			RoomRot _rot = static_cast<RoomRot>((_rotation % 360) / 90);

			_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, _rot, _redPixelFirstRoomPosBasedOnLevelCenter);
			const Vector2u& _newRoomSize = _room->GetSprite()->getTexture()->getSize();

			Vector2f _posRedPixelSecondRoom = _selectedDoor.GetPosition();
			Vector2f _baseOriginSecondRoomPos = _redPixelFirstRoomPosBasedOnLevelCenter - (Vector2f(_newRoomSize) / 2.0f);
			Vector2f _baseOriginRedPixel = _baseOriginSecondRoomPos + _posRedPixelSecondRoom;
			Vector2f _redPixelSecondRoomPosBasedOnLevelCenter = _baseOriginSecondRoomPos + _posRedPixelSecondRoom;
			Vector2f _centerSecondRoomOriginRedPixelDifference = FixRedPosition(_redPixelFirstRoomPosBasedOnLevelCenter - _redPixelSecondRoomPosBasedOnLevelCenter, _doorFirstRoom.owner->GetRotation());

			Vector2f _doorDirectionOffset = _doorFirstRoom.direction == 0 ? Vector2f(doorSize, -1.0f) : _doorFirstRoom.direction == 90 ? Vector2f(1.0f, doorSize) : _doorFirstRoom.direction == 180 ? Vector2f(-doorSize, 1.0f) : Vector2f(-1.0f, -doorSize);

			if (_doorFirstRoom.direction == 0) _room->GetSprite()->move(-_centerSecondRoomOriginRedPixelDifference + _doorDirectionOffset + Vector2f(1.0f, 1.0f));
			else if (_doorFirstRoom.direction == 90) _room->GetSprite()->move(Invert(_centerSecondRoomOriginRedPixelDifference, Vector2f(1.0f, -1.0f)) + _doorDirectionOffset + Vector2f(0.0f, 1.0f));
			else if (_doorFirstRoom.direction == 180) _room->GetSprite()->move(_centerSecondRoomOriginRedPixelDifference + _doorDirectionOffset);
			else if (_doorFirstRoom.direction == 270) _room->GetSprite()->move(-Invert(_centerSecondRoomOriginRedPixelDifference, Vector2f(1.0f, -1.0f)) + _doorDirectionOffset + Vector2f(1.0f, 0.0f));

			//_room->GetSprite()->setColor(Color(255, 255, 255, 50));

			_doorsOnNewRoom.erase(std::remove(_doorsOnNewRoom.begin(), _doorsOnNewRoom.end(), _selectedDoor), _doorsOnNewRoom.end());
		}

		_number--;
		currentRoomAmount++;
		if (!_room) return;
		if (_doorsOnNewRoom.empty()) continue;
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
	//const int _random = RandomInRange(0, _size - 1);
	const int _random = 0;
	const Door _door = doorPositions[_random];
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

float LevelGenerator::PositionOffset(const Door& _from, const Door& _to, const Vector2u& _newSize)
{
	Vector2f _oldRed = _from.GetPosition();
	Vector2f _newRed = _to.GetPosition();
	int _direction = _from.direction;
	if (_direction == 0) return (1 - (_newRed.x + 3) / _newSize.x) * _newSize.x;
	if (_direction == 90) return (1 - (_newRed.y + 3) / _newSize.x) * _newSize.x;
	if (_direction == 180) return -((1 - (_newRed.x + 2) / _newSize.x) * _newSize.x);
	return 0.0f;
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
Vector2f LevelGenerator::Invert(const Vector2f& _vector, const Vector2f& _multiplier)
{
	return Vector2f(_vector.y * _multiplier.x, _vector.x * _multiplier.y);
}
Vector2f LevelGenerator::FixRedPosition(const Vector2f& _vector, const float _rotation)
{
	cout << "Rotation: " << _rotation << endl;

	if (_rotation == 0) return _vector;
	if (_rotation == 90) return Invert(_vector, Vector2f(1.0f, 1.0f));
	if (_rotation == 180) return _vector * -1.0f;
	if (_rotation == 270) return Invert(_vector, Vector2f(-1.0f, -1.0f));
	return _vector;
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