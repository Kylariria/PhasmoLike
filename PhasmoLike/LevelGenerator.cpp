#include "LevelGenerator.h"
#include "WindowManager.h"
#include "VectorsUtils.h"

LevelGenerator::LevelGenerator()
{
	settings = GeneratorSettings();
}
LevelGenerator::LevelGenerator(const GeneratorSettings& _settings)
{
	settings = _settings;
	debugCenterRoom = new RectangleShape(Vector2f(3.0f, 3.0f));
	debugOriginRoom = new RectangleShape(Vector2f(3.0f, 3.0f));
	debugDoorRoom = new RectangleShape(Vector2f(3.0f, 3.0f));
	debugCenterRoom->setOrigin(1.5f, 1.5f);
	debugOriginRoom->setOrigin(1.5f, 1.5f);
	debugDoorRoom->setOrigin(1.5f, 1.5f);
	debugCenterRoom->setFillColor(Color::Green);
	debugOriginRoom->setFillColor(Color::Cyan);
	debugDoorRoom->setFillColor(Color::Magenta);
}
LevelGenerator::~LevelGenerator()
{
	delete debugCenterRoom;
	delete debugOriginRoom;
	delete debugDoorRoom;
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

			//_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, RoomRot::RR_TOP, Vector2f(0.0f, 0.0f));
			//_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, RoomRot::RR_RIGHT, Vector2f(0.0f, 0.0f));
			//_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, RoomRot::RR_BOTTOM, Vector2f(0.0f, 0.0f));
			_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, RoomRot::RR_LEFT, Vector2f(0.0f, 0.0f));

			const int _direction = _room->GetCurrentDirection();
			int _size = _doorsOnNewRoom.size();
			for (int _index = 0; _index < _size; _index++)
				_doorsOnNewRoom[_index].SetRotation(_direction + _doorsOnNewRoom[_index].GetCurrentDirection());
		}
		else
		{
			// ======== STEP1: Spawn room beside door opening ========

			// Get random door to spawn room beside
			const Door& _doorFirstRoom = GetRandomAvailableDoor();

			// Get random door on the room to spawn
			_doorsOnNewRoom = GetDoors(basePath + GetPathByType(_type) + "/1.txt");
			const Door& _selectedDoor = _doorsOnNewRoom[RandomInRange(0, _doorsOnNewRoom.size() - 1)];

			// Get rotation for new room
			int _rotation = GetOppositeRotation(_doorFirstRoom);
			RoomRot _rot = static_cast<RoomRot>((_rotation % 360) / 90);

			// Spawn new room (with base position => will set later)
			_room = new Room(basePath + GetPathByType(_type) + "/1.png", _type, _rot, Vector2f(0.0f, 0.0f));

			// Update forward and right vectors of doors
			const int _direction = _room->GetCurrentDirection();
			int _size = _doorsOnNewRoom.size();
			for (int _index = 0; _index < _size; _index++)
				_doorsOnNewRoom[_index].SetRotation(_direction + _doorsOnNewRoom[_index].GetCurrentDirection());

			// Get both rooms sizes based on their rotation
			Vector2f _firstRoomSize = Vector2f(_doorFirstRoom.owner->GetSprite()->getTexture()->getSize());
			Vector2f _newRoomSize = Vector2f(_room->GetSprite()->getTexture()->getSize());
			_firstRoomSize = GetSizeBasedOnRotation(_firstRoomSize, _doorFirstRoom.owner->GetCurrentDirection());
			_newRoomSize = GetSizeBasedOnRotation(_newRoomSize, _room->GetCurrentDirection());

			// Get distance
			Vector2f _distance = (Vector2f(_firstRoomSize) / 2.0f) + (Vector2f(_newRoomSize) / 2.0f);

			// Get forward vector of the first door since that's the one that wont rotate
			const Vector2f _firstDoorForwardVector = _doorFirstRoom.GetForwardVector();

			// Multiply distance with forward vector of the first room
			_distance = Vector2f(_distance.x * _firstDoorForwardVector.x, _distance.y * _firstDoorForwardVector.y);
			_room->GetSprite()->move(_distance);
			// =======================================================

			// ======== STEP2: Align both doors ========

			// Get Door position of first room (World relative)
			Vector2f _redPixelOffsetBasedOfFirstRoomOrigin = _doorFirstRoom.GetPosition();
			Vector2f _firstRoomCenterPos = _doorFirstRoom.owner->GetSprite()->getPosition();
			Vector2f _halfFirstRoomSize = _firstRoomSize / 2.0f;
			Vector2f _halfFirstRoomSizeRotated = VectorsUtils::RotateVectorOnlyNegate(_halfFirstRoomSize, _doorFirstRoom.owner->GetCurrentDirection());
			Vector2f _halfFirstRoomSizeForwardDirection = _firstRoomCenterPos - _halfFirstRoomSizeRotated;
			Vector2f _firstRoomOriginPos = _firstRoomCenterPos + _halfFirstRoomSizeForwardDirection;
			Vector2f _firstRedPixelWorldPos = _firstRoomOriginPos + VectorsUtils::RotateVector(_redPixelOffsetBasedOfFirstRoomOrigin, _doorFirstRoom.owner->GetCurrentDirection());

			// Get Door position of second room (World relative)
			Vector2f _secondRoomCenterPos = _room->GetSprite()->getPosition();
			Vector2f _forwardVectorSecondRoom = _room->GetForwardVector();
			Vector2f _rightVectorSecondRoom = _room->GetRightVector() * -1.0f;
			Vector2f _secondRoomSize = _newRoomSize;
			Vector2f _halfSecondRoomSize = _secondRoomSize / 2.0f;
			Vector2f _directionalVector = _forwardVectorSecondRoom + _rightVectorSecondRoom;
			_directionalVector.x = _directionalVector.x == 0 ? 1 : _directionalVector.x;
			_directionalVector.y = _directionalVector.y == 0 ? 1 : _directionalVector.y;
			Vector2f _originSecondRoom;
			_originSecondRoom.x = _halfSecondRoomSize.x * _directionalVector.x;
			_originSecondRoom.y = _halfSecondRoomSize.y * _directionalVector.y;
			_originSecondRoom += _secondRoomCenterPos;
			Vector2f _redPixelOffsetBasedOfSecondRoomOrigin = _selectedDoor.GetPosition();
			Vector2f _secondRedPixelWorldPos = _originSecondRoom + VectorsUtils::RotateVector(_redPixelOffsetBasedOfSecondRoomOrigin, _room->GetCurrentDirection());

			// Get difference between 2 red pixels positions and add door size
			Vector2f _difference = _firstRedPixelWorldPos - _secondRedPixelWorldPos;

			_difference = VectorsUtils::KeepHighestValue(_difference);

			if (_selectedDoor.GetCurrentDirection() == 0) _difference += Vector2f(1.0f, 0.0f);
			if (_selectedDoor.GetCurrentDirection() == 90) _difference += Vector2f(0.0f, 1.0f);

			if (_selectedDoor.GetCurrentDirection() == 0) _difference += Vector2f(-doorSize, 0.0f);
			if (_selectedDoor.GetCurrentDirection() == 90) _difference += Vector2f(0.0f, -doorSize);
			if (_selectedDoor.GetCurrentDirection() == 180) _difference += Vector2f(doorSize, 0.0f);
			if (_selectedDoor.GetCurrentDirection() == 270) _difference += Vector2f(0.0f, doorSize);

			if (_doorFirstRoom.owner->GetCurrentDirection() == 90)
			{
				if (_selectedDoor.GetCurrentDirection() == 0) _difference += Vector2f(-1.0f, 0.0f);
				if (_selectedDoor.GetCurrentDirection() == 180) _difference += Vector2f(-1.0f, 0.0f);
			}
			if (_doorFirstRoom.owner->GetCurrentDirection() == 180)
			{
				if (_selectedDoor.GetCurrentDirection() == 0) _difference += Vector2f(-1.0f, 0.0f);
				if (_selectedDoor.GetCurrentDirection() == 90) _difference += Vector2f(0.0f, -1.0f);
				if (_selectedDoor.GetCurrentDirection() == 180) _difference += Vector2f(-1.0f, 0.0f);
				if (_selectedDoor.GetCurrentDirection() == 270) _difference += Vector2f(0.0f, -1.0f);
			}
			if (_doorFirstRoom.owner->GetCurrentDirection() == 270)
			{
				if (_selectedDoor.GetCurrentDirection() == 90) _difference += Vector2f(0.0f, -1.0f);
				if (_selectedDoor.GetCurrentDirection() == 270) _difference += Vector2f(0.0f, -1.0f);
			}

			cout << "DIFFERENCE: " << _difference.x << " " << _difference.y << endl;

			_room->GetSprite()->move(_difference);

			//debugCenterRoom->setPosition(_secondRoomCenterPos);  // LIME
			//debugOriginRoom->setPosition(_originSecondRoom);  // CYAN
			//debugDoorRoom->setPosition(_secondRedPixelWorldPos); // MAGENTA








	




			//Vector2f _posRedPixelSecondRoom = _selectedDoor.GetPosition(); // Red pixel second door
			//Vector2f _secondRoomPos = _room->GetSprite()->getPosition(); // Center position of second room

			//Vector2f _baseOriginSecondRoomPosOffset = TurnVector(Vector2f(TurnVector(_newRoomSize, _room->GetRotation())) / 2.0f, _room->GetRotation());

			//_baseOriginSecondRoomPosOffset.x *= GetForwardVectorMultiplier(_room->GetForwardVector()).x;
			//_baseOriginSecondRoomPosOffset.y *= GetForwardVectorMultiplier(_room->GetForwardVector()).y;

			//Vector2f _baseOriginSecondRoomPos = _secondRoomPos + _baseOriginSecondRoomPosOffset;

			////_baseOriginSecondRoomPosOffset.x = _room->GetForwardVector().x != 0 ? _baseOriginSecondRoomPosOffset.x * _room->GetForwardVector().x : _baseOriginSecondRoomPosOffset.x;
			////_baseOriginSecondRoomPosOffset.y = _room->GetForwardVector().y != 0 ? _baseOriginSecondRoomPosOffset.y * _room->GetForwardVector().y : _baseOriginSecondRoomPosOffset.y;

			////Vector2f _baseOriginSecondRoomPos = _secondRoomPos + Vector2f(_newRoomSize) / 2.0f; // Top Left position of the second room
			////Vector2f _baseOriginSecondRoomPos;
			////_baseOriginSecondRoomPos.x = _secondRoomPos.x - (_room->GetForwardVector().y != 0 ? _room->GetForwardVector().y * _newRoomSize.x : _newRoomSize.x) / 2.0f;
			////_baseOriginSecondRoomPos.y = _secondRoomPos.y - (_room->GetForwardVector().x != 0 ? _room->GetForwardVector().x * _newRoomSize.y : _newRoomSize.y) / 2.0f;

			//Vector2f _redPixelSecondRoomPosBasedOnLevelCenter = _baseOriginSecondRoomPos + TurnVector(_posRedPixelSecondRoom, _room->GetRotation());

			//cout << "BEFORE: " << _newRoomSize.x << " " << _newRoomSize.y << endl;
			//cout << "AFTER: " << TurnVector(_newRoomSize, _rotation).x << " " << TurnVector(_newRoomSize, _rotation).y << endl;
			//cout << "ROTATION: " << _rotation << endl;

			//// Get difference between 2 red pixels positions
			//Vector2f _difference =  _redPixelFirstRoomPosBasedOnLevelCenter - _redPixelSecondRoomPosBasedOnLevelCenter;
			//// ==> The 2 red pixels are above each others
			//
			//// ==> move new room (doorSize) to the same direction as _difference
			//if (!(_room->GetRotation() == 0 || _room->GetRotation() == 90))
			//{
			//	_difference.x += _difference.x == 0 ? 0 : doorSize;
			//	_difference.y += _difference.y == 0 ? 0 : doorSize;
			//	_room->GetSprite()->move(_difference);
			//}
			//else
			//{
			//	_difference.x += _difference.x == 0 ? 0 : (doorSize * 2.0f) + 2;
			//	_difference.y += _difference.y == 0 ? 0 : (doorSize * 2.0f) + 2;
			//	_room->GetSprite()->move(-_difference);
			//}
			//// =========================================

			//// ======== FIX DOOR DISTANCES ========
			//Vector2f _forwardSecondRoom = _room->GetForwardVector();
			//Vector2f _offset = _firstRoomSize / 2.0f;
			//_offset.x *= _forwardSecondRoom.x;
			//_offset.y *= _forwardSecondRoom.y;
			//_room->GetSprite()->move(_offset);
			//// ====================================




				/*
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
			*/
			_room->GetSprite()->setColor(Color(255, 255, 255, 50));

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
Vector2f LevelGenerator::GetForwardVectorMultiplier(const Vector2f& _vector)
{
	if (_vector == Vector2f(0.0f, 1.0f)) return Vector2f(1.0f, 1.0f);
	if (_vector == Vector2f(-1.0f, 0.0f)) return Vector2f(1.0f, -1.0f);
	if (_vector == Vector2f(0.0f, -1.0f)) return Vector2f(-1.0f, -1.0f);
	if (_vector == Vector2f(1.0f, 0.0f)) return Vector2f(-1.0f, 1.0f);
	return Vector2f(1.0f, 1.0f);
}

Vector2f LevelGenerator::FixDoorDistance(const Vector2f& _vector, const int& _direction)
{
	cout << "DEBUGGGGGGGGGGGG: " << _direction << " " << _vector.x << " " << _vector.y << endl;
	if (_direction == 0) return Vector2f(_vector.y, _vector.x);
	else
	{
		cout << "ERROR WHILE FIXING DOOR DISTANCE" << endl;
		return _vector;
	}
}

Vector2f LevelGenerator::GetSizeBasedOnRotation(const Vector2f& _vector, const int& _direction)
{
	if (_direction == 90 || _direction == 270) return Vector2f(_vector.y, _vector.x);
	return _vector;
}

string LevelGenerator::GetPathByType(const RoomType& _type)
{
	string _pathList[] = { "Bedrooms", "Kitchens", "Livingrooms", "Garages", "Corridors", "Bathrooms" };
	return _pathList[static_cast<int>(_type)];
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
	int _direction = _from.GetCurrentDirection();
	if (_direction == 0) return (1 - (_newRed.x + 3) / _newSize.x) * _newSize.x;
	if (_direction == 90) return (1 - (_newRed.y + 3) / _newSize.x) * _newSize.x;
	if (_direction == 180) return -((1 - (_newRed.x + 2) / _newSize.x) * _newSize.x);
	return 0.0f;
}
int LevelGenerator::GetOppositeRotation(const Door& _from)
{
	if (_from.GetCurrentDirection() == 0) return 180;
	if (_from.GetCurrentDirection() == 90) return 270;
	if (_from.GetCurrentDirection() == 180) return 0;
	if (_from.GetCurrentDirection() == 270) return 90;
	return 0;
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

Vector2f LevelGenerator::TurnVector(const Vector2f& _vector, const int& _direction)
{
	if (_direction == 0) return Vector2f(_vector.x, _vector.y);
	else if (_direction == 90) return Vector2f(-_vector.y, _vector.x);
	else if (_direction == 180) return Vector2f(-_vector.x, -_vector.y);
	else if (_direction == 270) return Vector2f(_vector.y, -_vector.x);
	else
	{
		cout << "ERROR TURNING VECTOR" << endl;
		return Vector2f(0.0f, 0.0f);
	}
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