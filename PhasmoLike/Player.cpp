#include "Player.h"
#include "MovementComponent.h"

void Player::SetNewCharacterLocTarget(const Vector2f& _pos)
{
	MovementComponent* _mouv = character->GetComponent<MovementComponent>();
	if(!_mouv) return;
	_mouv->SetTargetLocation(_pos);
}

Player::Player()
{
	character = new Character("Player", Vector2f(0.0f, 0.0f), Vector2f(25.0f, 25.0f), "");
	character->SetOriginAtMiddle();
}
