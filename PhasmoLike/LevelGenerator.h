#pragma once

#include <iostream>

using namespace std;

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
	string levelStyle;

public:
	LevelGenerator();
	LevelGenerator(const GeneratorSettings& _settings);

private:
	bool CheckValidity();

public:
	void Generate(const string& _levelStyle);
};