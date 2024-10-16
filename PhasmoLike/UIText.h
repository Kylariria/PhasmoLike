#pragma once

#include "UIElements.h"


class UIText : public UIElements
{
	Font font;
	int* value;
	string textValue;
	Text* text;

public:
	Text* GetText() const
	{
		return text;
	}

public:
	UIText(const string& _id, const Vector2f& _position, const Color& _color, const string& _textValue, const int _textSize, const string& _fontPath, bool _italic = false, int* _additionalValue = nullptr);
	~UIText();

public:
	virtual void Update(const Vector2i& _mousePosition) override;
	virtual vector<Drawable*> GetDrawables() override;
};