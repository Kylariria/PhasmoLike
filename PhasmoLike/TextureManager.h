#pragma once
#include "IManager.h"
#include "Singleton.h"
#include "TextureData.h"

class TextureManager : public Singleton<TextureManager>, public IManager<string, TextureData>
{

public:
	void LoadTexture(Shape* _shape, const string& _path);
};

