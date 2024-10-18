#include "Inventory.h"
#include "InventorySlot.h"
#include "WindowManager.h"
#include "TextureManager.h"
#include "Item.h"

Inventory::Inventory()
{
	slotsAmount = 3;
	inventoryWindow = new CustomWindow("inventory", "Inventory", 300, 450, Vector2i(90, 50), true);
	WindowManager::GetInstance().SetupPosition(inventoryWindow);
	inventoryWindow->SetColor(Color(255, 255, 255, 128));
	Init();
}
Inventory::~Inventory()
{
	delete background;
	for (InventorySlot* _slot : allSlots)
		delete _slot;
}
bool Inventory::AddItem(Item* _itemToAdd)
{
	if (GetItemAmount() >= slotsAmount) return false;

	for (int _index = 0; _index < slotsAmount; _index++)
	{
		if (allSlots[_index]->GetItem()) continue;
		allSlots[_index]->SetItem(_itemToAdd);
		_itemToAdd->GetSprite()->setPosition(allSlots[_index]->GetPosition() - Vector2f(75.0f, 0.0f));
		return true;
	}
	return false;
}

bool Inventory::ToggleInventory()
{
	bool _current = inventoryWindow->IsHidden();
	_current = !_current;
	inventoryWindow->SetHidden(_current);
	return !_current;
}
vector<Item*> Inventory::GetItems() const
{
	vector<Item*> _items;
	for (InventorySlot* _slot : allSlots)
	{
		Item* _item = _slot->GetItem();
		if (_item)
			_items.push_back(_item);
	}
	return _items;
}
int Inventory::GetItemAmount() const
{
	return GetItems().size();
}
void Inventory::Init()
{
	InitBackground();
	InitSlots();
}

void Inventory::InitBackground()
{
	background = new RectangleShape(Vector2f(2733.0f, 3962.0f));
	TextureManager::GetInstance().LoadTexture(background, "Resources/Images/Inventory.png");
	background->setScale(300 / 2733.0f, 450 / 3962.0f);
	inventoryWindow->AddDrawable(background);
}
void Inventory::InitSlots()
{
	const float& _offsetX = 300.0f / 2.0f;
	const float& _offsetY = 450.0f / (slotsAmount + 1.0f);

	for (int _index = 0; _index < slotsAmount; _index++)
		allSlots.push_back(new InventorySlot(Vector2f(_offsetX, _offsetY * (_index + 1) + 25.0f), this));
}