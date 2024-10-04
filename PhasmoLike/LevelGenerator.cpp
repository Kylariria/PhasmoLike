#include "LevelGenerator.h"

LevelGenerator::LevelGenerator()
{
	settings = GeneratorSettings();
	levelStyle = "";
}
LevelGenerator::LevelGenerator(const GeneratorSettings& _settings)
{
	settings = _settings;
	levelStyle = "";
}

bool LevelGenerator::CheckValidity()
{
	if (!settings.IsValid()) return false;
	return true;
}
void LevelGenerator::Generate(const string& _levelStyle)
{
	if (!CheckValidity()) return;
	levelStyle = _levelStyle;
	// TODO
}