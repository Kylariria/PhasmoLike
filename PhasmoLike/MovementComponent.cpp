#include "MovementComponent.h"

MovementComponent::MovementComponent(Entity* _owner, float _speed) : Component(_owner)
{
	speed = _speed;
}

void MovementComponent::SetTargetLocation(const Vector2f& _targetPos)
{
	targetPos = _targetPos;
	isMoving = true;
}

void MovementComponent::Move(const float& _deltaTime)
{
	Shape* _shape = owner->GetShape();
	Vector2f _direction = targetPos - _shape->getPosition();
	_direction /= Length(_direction);
	_shape->setPosition(_shape->getPosition() + _direction * speed * _deltaTime);
}

bool MovementComponent::IsAtLocation()
{
	Shape* _shape = owner->GetShape();
	const float& _distance = static_cast<float>(sqrt(pow(_shape->getPosition().x - targetPos.x, 2) + pow(_shape->getPosition().y - targetPos.y, 2)));

	canMove = _distance < .50f ? false : true;
	isMoving = canMove ? true : false;
	return _distance < .50f;
}

float MovementComponent::Length(const Vector2f& _vec)
{
	return static_cast<float>(sqrt(pow(_vec.x, 2) + pow(_vec.y, 2)));
}

void MovementComponent::Update(const float& _deltaTime)
{
	if(!isMoving) return;
	if (IsAtLocation() && !canMove) return;
	Move(_deltaTime);
}
