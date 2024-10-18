#pragma once

#include "Inventory.h"
#include "Item.h"

class InventorySlot
{
	RectangleShape* backgroundTexture = nullptr;
	Item* item = nullptr;
	Inventory* inventoryRef;
	Text* text = nullptr;
	Font* font = nullptr;

public:
	Vector2f GetPosition() const
	{
		return backgroundTexture->getPosition();
	}
	void SetItem(Item* _item)
	{
		CustomWindow* _window = inventoryRef->GetWindow();
		if (item)
		{
			_window->RemoveDrawable(item->GetSprite(), false);
			delete item;
		}
		item = _item;
		_window->AddDrawable(item->GetSprite());
		SetText(item->GetName());
	}
	Item* GetItem() const
	{
		return item;
	}

public:
	InventorySlot(const Vector2f& _position, Inventory* _inventory);
	~InventorySlot();

private:
	void Init();
	void InitText();
	void SetText(const string& _text);
};