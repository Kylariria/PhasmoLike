#pragma once

#include <vector>

#include "Item.h"
#include "CustomWindow.h"

using namespace std;

class Inventory
{
	vector<Item*> items;
	int slotsAmount;
	CustomWindow* inventoryWindow;

public:
	vector<Item*> GetItems() const {
		return items;
	}

public:
	Inventory();

public:
	bool AddItem(Item* _itemToAdd);
	bool ToggleInventory();
};