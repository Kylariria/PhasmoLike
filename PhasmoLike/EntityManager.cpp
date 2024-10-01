#include "EntityManager.h"

void EntityManager::UpdateAllEntities()
{
	const float& _deltaTime = 0.01f;

	const vector<Entity*>& _entities = GetAllValues();
	for (Entity* _entity : _entities)
	{
		if (_entity)
		{
			_entity->Update(_deltaTime);
		}
	}

}

void EntityManager::DisplayAllEntities(RenderWindow* _window) 
{
	const vector<Entity*> _allEntities = GetValues();

	for (const Entity* _entity : _allEntities)
	{
		_window->draw(*_entity->GetShape());
	}
}
