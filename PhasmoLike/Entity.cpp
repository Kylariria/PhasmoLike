#include "Entity.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "Component.h"
#include "CustomWindow.h"
#include "WindowManager.h"

Entity::Entity(const string& _name, const Vector2f& _position, const Vector2f& _size, const string& _path, CustomWindow* _whereToDisplay) : IManagable(_name)
{
	shape = new RectangleShape(_size);
	shape->setPosition(_position);
	Register();
	TextureManager::GetInstance().LoadTexture(shape, _path);
	SetWhereToDisplay(_whereToDisplay);
}

Entity::Entity(const string& _name, const Vector2f& _position, const float& _size, const string& _path, CustomWindow* _whereToDisplay) : IManagable(_name)
{
	shape = new CircleShape(_size);
	shape->setPosition(_position);
	Register();
	TextureManager::GetInstance().LoadTexture(shape, _path);
	SetWhereToDisplay(_whereToDisplay);
}

Entity::Entity(const string& _name, const Vector2f& _position, const string& _path, CustomWindow* _whereToDisplay) : IManagable(_name)
{
	sprite = TextureManager::GetInstance().CreateSprite(_path);
	sprite->setPosition(_position);
	Register();
	SetWhereToDisplay(_whereToDisplay);
}

Entity::~Entity()
{
	if(shape)
		delete shape;
	if(sprite)
		delete sprite;

	for (Component* _component : components)
	{
		delete _component;
	}
	components.clear();
}

void Entity::Register()
{
	EntityManager::GetInstance().Add(id,this);
}

void Entity::SetWhereToDisplay(CustomWindow* _whereToDisplay)
{
	if (!shape) return;
	if (!_whereToDisplay)
	{	
		cout << "Pas de window" << endl;
		CustomWindow* _window = WindowManager::GetInstance().Get("main");
		if (!_window) return;
		_window->AddDrawable(shape);
		return;
	}
	_whereToDisplay->AddDrawable(shape);
}

void Entity::AddComponent(Component* _component)
{
	components.push_back(_component);
}

void Entity::Update(float _deltaTime)
{
	for (Component* _component : components)
	{
		_component->Update(_deltaTime);
	}
}
