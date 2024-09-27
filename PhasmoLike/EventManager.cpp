#include "EventManager.h"

void EventManager::AddEvent(CustomEvent* _event)
{
	if (!_event) return;
	if (Exist(_event->GetName()))
	{
		cout << "Event " << _event->GetName() << " already exist" << endl;
		return;
	}
	events.push_back(_event);
	size++;
}

void EventManager::AddEvent(const string& _name, const vector<function<void()>>& _functions)
{
	if (Exist(_name)) return;
	bool _haveCallback = _functions.empty() ? false : true;
	_haveCallback ? new CustomEvent(_name, _functions) :
		new CustomEvent(_name);
}

bool EventManager::Exist(const string& _name)
{
	const int _size = int(events.size());
	for (int _index = 0; _index < _size; _index++)
	{
		CustomEvent* _event = events[_index];
		if (_event->GetName() == _name)
		{
			return true;
		}
	}
	return false;
}
EventManager::~EventManager()
{
	for (CustomEvent* _event : events)
	{
		delete _event;
	}
	events.clear();
}
