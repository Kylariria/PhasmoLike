#include "Item.h"
#include "TextureManager.h"

Item::Item()
{
	name = "Unnamed";
	Init("");
}
Item::~Item()
{
	if (sprite)
		delete sprite;
}
Item::Item(const string& _name, const string& _path)
{
	name = _name;
	Init(_path);
}

void Item::Init(const string& _path)
{
	if (_path.empty()) return;
	sprite = TextureManager::GetInstance().CreateSprite(_path);
	sprite->setScale(0.4f, 0.4f);
	sprite->setOrigin(Vector2f(sprite->getTexture()->getSize()) / 2.0f);
}