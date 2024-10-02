#include "Inventory.h"
#include "WindowManager.h"

Inventory::Inventory()
{
	slotsAmount = 3;
	inventoryWindow = new CustomWindow("inventory", "Inventory", 300, 600, Vector2i(85, 50), true);
	WindowManager::GetInstance().SetupPosition(inventoryWindow);
}
bool Inventory::AddItem(Item* _itemToAdd)
{
	if (items.size() >= slotsAmount) return false;
	items.push_back(_itemToAdd);
	return true;
}

bool Inventory::ToggleInventory()
{
	bool _current = inventoryWindow->IsHidden();
	_current = !_current;
	inventoryWindow->SetHidden(_current);
	return !_current;
}