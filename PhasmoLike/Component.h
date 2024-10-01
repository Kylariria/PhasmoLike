#pragma once
#include "Entity.h"

class Component
{
protected:
	Entity* owner;
	

public:
	Component(Entity* _owner);
	
public:
	virtual void Update(const float& _deltaTime) {};
};

