#pragma once

#include <vector>

#include "CustomWindow.h"

class InventorySlot;
class Item;

using namespace std;

class Inventory
{
	int slotsAmount;
	CustomWindow* inventoryWindow;
	RectangleShape* background = nullptr;
	vector<InventorySlot*> allSlots;

public:
	CustomWindow* GetWindow() const
	{
		return inventoryWindow;
	}

public:
	Inventory();
	~Inventory();

private:
	void Init();
	void InitBackground();
	void InitSlots();

public:
	bool AddItem(Item* _itemToAdd);
	bool ToggleInventory();
	vector<Item*> GetItems() const;
	int GetItemAmount() const;
};