#include "InventorySlot.h"
#include "TextureManager.h"

InventorySlot::InventorySlot(const Vector2f& _position, Inventory* _inventory)
{
	inventoryRef = _inventory;
	Init();
	backgroundTexture->setPosition(_position);
	InitText();
}

InventorySlot::~InventorySlot()
{
	delete backgroundTexture;
	delete item;
	if (font)
		delete font;
	if (text)
		delete text;
}

void InventorySlot::Init()
{
	backgroundTexture = new RectangleShape(Vector2f(1718.0f, 673.0f));
	TextureManager::GetInstance().LoadTexture(backgroundTexture, "Resources/Images/Slot.png");
	backgroundTexture->setScale(300 / 1718.0f * 0.8f, 300 / 1718.0f * 0.8f);
	backgroundTexture->setOrigin(backgroundTexture->getSize() / 2.0f);
	inventoryRef->GetWindow()->AddDrawable(backgroundTexture);
}

void InventorySlot::InitText()
{
	font = new Font();
	if (!font->loadFromFile("Resources/Fonts/OctoberCrow.ttf"))
	{
		cerr << "Error while loading font for inventory slot." << endl;
		return;
	}
	text = new Text();
	text->setFont(*font);
	text->setPosition(backgroundTexture->getPosition() - Vector2f(10.0f, 20.0f));
	text->setFillColor(Color::Black);
	inventoryRef->GetWindow()->AddDrawable(text);
}

void InventorySlot::SetText(const string& _text)
{
	if (text)
		text->setString(_text);
}