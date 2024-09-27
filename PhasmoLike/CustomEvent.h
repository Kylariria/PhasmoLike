#pragma once
#include <iostream>
#include <vector>
#include <functional>

using namespace std;


class CustomEvent
{
	string name = "";
	vector<function<void()>> functions = {};

public:
	CustomEvent(const string& _name, const vector<function<void()>>& _functions);
	CustomEvent(const string& _name);

public:
	string GetName() const
	{
		return name;
	}

public:
	void AddCallback(const function<void()>& _function);
	void Register();
	void Broadcast();
};

