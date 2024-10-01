#pragma once
#include "Character.h"

class Player
{
	Character* character;

public:
	Character* GetCharacter() const { return  character; }

public:
	void SetNewCharacterLocTarget(const Vector2f& _pos);

public:
	Player();
};

