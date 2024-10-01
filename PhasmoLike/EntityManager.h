#pragma once
#include "Entity.h"
#include "Singleton.h"
#include "IManager.h"


class EntityManager : public Singleton<EntityManager>, public IManager<string,Entity>
{
public:
	void UpdateAllEntities();
	void DisplayAllEntities(RenderWindow* _window);
};

