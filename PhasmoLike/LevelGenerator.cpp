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
void LevelGenerator::Generate()
{
	if (!CheckValidity()) return;
	// TODO
}