#include "EntityManager.h"
#include "TimerManager.h"

void EntityManager::UpdateAllEntities()
{
	const float& _deltaTime = TimerManager::GetInstance().GetDeltaTime();

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
	const vector<Entity*> _allEntities = GetAllValues();

	for (const Entity* _entity : _allEntities)
	{
		_window->draw(*_entity->GetShape());
	}
}
