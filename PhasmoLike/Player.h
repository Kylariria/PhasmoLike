#pragma once

#include "Character.h"
#include "Inventory.h"

class Player
{
	Character* character;
	Inventory* inventory;

public:
	Character* GetCharacter() const { return  character; }
	void SetNewCharacterLocTarget(const Vector2f& _pos);

public:
	Player();
	~Player();

private:
	void Init();
	void InitInputs();

public:
	void ToggleInventory();
};

