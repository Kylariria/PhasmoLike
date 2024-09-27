#pragma once
#pragma once
#include "CustomEvent.h"
#include <iostream>
#include "Singleton.h"
#include <vector>

using namespace std;

class EventManager : public Singleton<EventManager>
{
	vector<CustomEvent*> events;
	int size = 0;

public:
	~EventManager();

public:

	CustomEvent* GetEvent(const string& _name) const
	{
		for (int _index = 0; _index < size; _index++)
		{
			CustomEvent* _customEvent = events[_index];
			if (_customEvent->GetName() == _name)
			{
				return _customEvent;
			}
		}
		return nullptr;
	}

public:
	void AddEvent(CustomEvent* _event);
	void AddEvent(const string& _name, const vector<function<void()>>& _functions = {});

private:

	bool Exist(const string& _name);

};

