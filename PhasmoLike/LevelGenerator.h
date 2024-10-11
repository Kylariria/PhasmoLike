#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Room.h"

using namespace std;
using namespace sf;

struct Door : public IDirections
{
	Room* owner;
	int posX = 0; // In pixels based of on the texture
	int posY = 0; // In pixels based of on the texture

public:
	Door(const int& _posX, const int& _posY, const int& _direction)
	{
		posX = _posX;
		posY = _posY;
		SetRotation(_direction);
	}

public:
	Vector2f GetPosition() const { return Vector2f(static_cast<float>(posX), static_cast<float>(posY)); }

public:
	bool operator==(const Door& _door)
	{
		return posX == _door.posX && posY == _door.posY;
	}
};

struct GeneratorSettings
{
	// Rooms amounts
	int kitchens = 0;
	int garages = 0;
	int bedrooms = 0;
	int bathrooms = 0;
	int corridors = 0;
	int livingrooms = 0;
	int globalAmount = 0;

public:
	bool IsValid() const { return globalAmount > 0; }

public:
	GeneratorSettings()
	{
		kitchens = 0;
		garages = 0;
		bedrooms = 0;
		bathrooms = 0;
		corridors = 0;
		livingrooms = 0;
		ComputeGlobalAmount();
	}
	GeneratorSettings(const int& _kitchens, const int& _garages, const int& _bedrooms, const int& _bathrooms, const int& _corridors, const int& _livingrooms)
	{
		kitchens = _kitchens;
		garages = _garages;
		bedrooms = _bedrooms;
		bathrooms = _bathrooms;
		corridors = _corridors;
		livingrooms = _livingrooms;
		ComputeGlobalAmount();
	}

private:
	void ComputeGlobalAmount()
	{
		globalAmount = kitchens + garages + bedrooms + bathrooms + corridors + livingrooms;
	}
};

class LevelGenerator
{
	GeneratorSettings settings;
	string basePath;
	int currentRoomAmount = 0;
	vector<Door> doorPositions;
	int doorSize = 54;

	// TODO temp
public:
	RectangleShape* debugCenterRoom = nullptr;
	RectangleShape* debugOriginRoom = nullptr;
	RectangleShape* debugDoorRoom = nullptr;

public:
	LevelGenerator();
	LevelGenerator(const GeneratorSettings& _settings);
	~LevelGenerator();

private:
	bool CheckValidity();
	void GenerateRooms(int _number, const RoomType& _type);
	string GetPathByType(const RoomType& _type);
	Door GetRandomAvailableDoor();
	vector<Door> GetDoors(const string& _path);
	int GetOppositeRotation(const Door& _from);
	int RandomInRange(const int& _min, const int& _max);
	int NormalizeRotation(int _value);
	float PositionOffset(const Door& _from, const Door& _to, const Vector2u& _newSize);
	Vector2f Invert(const Vector2f& _vector, const Vector2f& _multiplier);
	Vector2f FixRedPosition(const Vector2f& _vector, const float _rotation);
	Vector2f TurnVector(const Vector2f& _vector, const int& _direction);
	Vector2f GetForwardVectorMultiplier(const Vector2f& _vector);
	Vector2f FixDoorDistance(const Vector2f& _vector, const int& _direction);
	Vector2f GetSizeBasedOnRotation(const Vector2f& _vector, const int& _direction);

public:
	void Generate(const string& _levelStyle);
};