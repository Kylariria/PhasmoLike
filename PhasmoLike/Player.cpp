#include "Player.h"
#include "MovementComponent.h"
#include "Action.h"
#include "InputManager.h"
#include "WindowManager.h"

void Player::SetNewCharacterLocTarget(const Vector2f& _pos)
{
	MovementComponent* _mouv = character->GetComponent<MovementComponent>();
	if(!_mouv) return;
	_mouv->SetTargetLocation(_pos);
	cout << "SetNewCharacterLocTarget at " << _pos.x << ", " << _pos.y << "" << endl;
}

Player::Player()
{
	character = new Character("Player", Vector2f(0.0f, 0.0f), Vector2f(25.0f, 25.0f), "");
	inventory = new Inventory();
	Init();
}
Player::~Player()
{
	delete inventory;
}
void Player::InitInputs()
{
	new Action(ActionData("Move", [this]() {
		const Vector2f& _target = Vector2f(Mouse::getPosition(*WindowManager::GetInstance().GetMainWindow()));
		SetNewCharacterLocTarget(_target);
	}, InputTypeData(ActionType::MouseButtonPressed, Mouse::Left)), "Player");

	new Action(ActionData("ToggleInventory", [this]() { ToggleInventory(); }, InputTypeData(ActionType::KeyPressed, Keyboard::E)), "Player");
}
void Player::Init()
{
	InitInputs();
}
void Player::ToggleInventory()
{
	inventory->ToggleInventory();
}
