#include "TextureManager.h"

void TextureManager::LoadTexture(Shape* _shape, const string& _path)
{
	if (_path == "") return;
	TextureData* _texture = Get(_path);

	if (!_texture)
	{
		_texture = new TextureData(_path);
		if (!_texture->loadFromFile(_path))
		{
			cerr << "Error loading texture: " << _path << endl;
		}
	}

	_shape->setTexture(_texture);
}
