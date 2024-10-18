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
		// TODO complete
		// new Room();
		// basePath + _texturePath + ".png"
		// GetRandomAvailablePosition()
		new Room(basePath + GetPathByType(_type) + ".png", _type, RoomRot::RR_RANDOM, GetRandomAvailablePosition());
		_number--;
		currentRoomAmount++;
	}
}
string LevelGenerator::GetPathByType(const RoomType& _type)
{
	string _pathList[] = { "Bedrooms", "Kitchens", "Livingrooms", "Garages", "Corridors", "Bathrooms" };
	return _pathList[0];
}
Vector2f LevelGenerator::GetRandomAvailablePosition()
{
	const int _size = static_cast<int>(doorPositions.size());
	if (_size == 0) return Vector2f(0.0f, 0.0f);
	const int _randomIndex = rand() % _size;
	const Vector2f& _position = doorPositions[_randomIndex];
	doorPositions.erase(doorPositions.begin() + _randomIndex);
	return _position;
}
void LevelGenerator::Generate(const string& _levelStyle)
{
	if (!CheckValidity()) return;
	currentRoomAmount = 0;
	basePath = "Resources/Maps/" + _levelStyle + "/";

	GenerateRooms(settings.bathrooms, RoomType::BATHROOM);
	GenerateRooms(settings.bedrooms, RoomType::BEDROOM);
	GenerateRooms(settings.corridors, RoomType::CORRIDOR);
	GenerateRooms(settings.garages, RoomType::GARAGE);
	GenerateRooms(settings.kitchens, RoomType::KITCHEN);
	GenerateRooms(settings.livingrooms, RoomType::LIVINGROOM);

}