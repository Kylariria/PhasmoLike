#include "Player.h"
#include "MovementComponent.h"
#include "Action.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "CameraManager.h"

void Player::SetNewCharacterLocTarget(const Vector2f& _pos)
{
	MovementComponent* _mouv = character->GetComponent<MovementComponent>();
	if(!_mouv) return;
	_mouv->SetTargetLocation(_pos);
}

Player::Player()
{
	character = new Character("Player", Vector2f(0.0f, 0.0f), Vector2f(25.0f, 25.0f), "Resources/Images/Player/idle.png");
	character->SetOriginAtMiddle();
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
		CustomWindow* _window = WindowManager::GetInstance().GetMainWindow();
		const Vector2i& _target = Mouse::getPosition(*_window);
		Camera* _camera = CameraManager::GetInstance().GetMainCamera();
		const Vector2f& _worldPos = _window->mapPixelToCoords(_target, *_camera);
		SetNewCharacterLocTarget(_worldPos);
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
