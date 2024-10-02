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
	Texture* _texture = nullptr;
	RectangleShape* _background = nullptr;

public:
	vector<Item*> GetItems() const {
		return items;
	}

public:
	Inventory();
	~Inventory();

private:
	void Init();

public:
	bool AddItem(Item* _itemToAdd);
	bool ToggleInventory();
};