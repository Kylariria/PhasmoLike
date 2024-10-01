#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

using namespace sf;

class MovementComponent : public Component
{
	float speed;
	Vector2f targetPos;
	bool canMove = true;
	bool isMoving = false;

public:
	MovementComponent(Entity* _owner, float _speed);

public:
	void SetTargetLocation(const Vector2f& _targetPos);

public:
	void Move(const float& _deltaTime);
	bool IsAtLocation();
	float Length(const Vector2f& _vec);
public:

	virtual void Update(const float& _deltaTime) override;
};

