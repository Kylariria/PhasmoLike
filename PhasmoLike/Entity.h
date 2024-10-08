#pragma once
#include "IManagable.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


using namespace std;
using namespace sf;

class CustomWindow;
class Component;
class Entity : public IManagable<string>
{
	Shape* shape = nullptr;
	Sprite* sprite = nullptr;
	vector<Component*> components = {};

public:
	Shape* GetShape() const { return shape; }
	inline void SetOriginAtMiddle() { shape->setOrigin(shape->getLocalBounds().width / 2, shape->getLocalBounds().height / 2); }
	inline void SetOriginAtMiddleSprite() { sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2); }

public:
	Entity(const string& _name,const Vector2f& _position, const Vector2f& _size,const string& _path,CustomWindow* _whereToDisplay = nullptr);
	Entity(const string& _name,const Vector2f& _position, const float& _size,const string& _path, CustomWindow* _whereToDisplay = nullptr);
	Entity(const string& _name, const Vector2f& _position, const string& _path, CustomWindow* _whereToDisplay = nullptr);
	~Entity();

private:
	virtual void Register() override;
	void SetWhereToDisplay(CustomWindow* _whereToDisplay);
protected:

public:
	void AddComponent(Component* _component);
	virtual void Update(float _deltaTime);

	template<typename T>
	T* GetComponent()
	{
		for (Component* _component : components)
		{
			T* _result = dynamic_cast<T*>(_component);
			if (_result) return _result;
		}
		return nullptr;
	}
};

