#include "Inventory.h"
#include "WindowManager.h"

Inventory::Inventory()
{
	slotsAmount = 3;
	inventoryWindow = new CustomWindow("inventory", "Inventory", 300, 450, Vector2i(85, 50), true, Style::None);
	WindowManager::GetInstance().SetupPosition(inventoryWindow);
	inventoryWindow->SetColor(Color(255, 255, 255, 128));
	Init();
}
Inventory::~Inventory()
{
	delete _texture;
	delete _background;
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
void Inventory::Init()
{
	_texture = new Texture();
	if (!_texture->loadFromFile("Resources/Images/Inventory.png"))
	{
		return;
	}
	_background = new RectangleShape(Vector2f(2733.0f, 3962.0f));
	_background->setTexture(_texture);
	_background->setScale(300 / 2733.0f, 450 / 3962.0f);
	inventoryWindow->AddDrawable(_background);
}