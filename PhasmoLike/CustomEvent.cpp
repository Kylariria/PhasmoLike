#include "CustomEvent.h"
#include "EventManager.h"
CustomEvent::CustomEvent(const string& _name, const vector<function<void()>>& _functions)
{
	name = _name;
	functions = _functions;
	Register();
}

CustomEvent::CustomEvent(const string& _name)
{
	name = _name;
	Register();
}

void CustomEvent::AddCallback(const function<void()>& _function)
{
	if (!_function) return;
	functions.push_back(_function);
}

void CustomEvent::Register()
{
	EventManager::GetInstance().AddEvent(this);
}

void CustomEvent::Broadcast()
{
	for (const function<void()>& _function : functions)
	{
		_function();
	}
}

