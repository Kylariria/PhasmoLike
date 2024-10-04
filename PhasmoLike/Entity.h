#pragma once
#include "IManagable.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


using namespace std;
using namespace sf;

class Component;
class Entity : public IManagable<string>
{
	Shape* shape = nullptr;
	vector<Component*> components = {};

public:
	Shape* GetShape() const { return shape; }
	inline void SetOriginAtMiddle() { shape->setOrigin(shape->getLocalBounds().width / 2, shape->getLocalBounds().height / 2); }

public:
	Entity(const string& _name,const Vector2f& _position, const Vector2f& _size,const string& _path);
	Entity(const string& _name,const Vector2f& _position, const float& _size,const string& _path);
	~Entity();

private:
	virtual void Register() override;

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
	}
};

