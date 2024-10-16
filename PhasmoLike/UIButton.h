#pragma once

#include <functional>
#include "UIElements.h"

using namespace sf;
using namespace std;

class UIButton : public UIElements
{
	FloatRect box;
	Color unhoverColor;
	Color hoverColor;
	function<void()> callback;
	vector<UIElements*> elements;
	bool isHover;
	string soundPath;

public:
	bool IsHover() const
	{
		return isHover;
	}

public:
	UIButton(const string& _id, const Vector2f& _position, const Color& _unhoverColor, const Color& _hoverColor, const string& _textValue, const int _textSize, const string& _fontPath, const string& _soundPath, const function<void()>& _callback, int* _additionalValue = nullptr);
	UIButton(const string& _id, const Vector2f& _position, const Color& _unhoverColor, const Color& _hoverColor, const string& _path, const Vector2f& _imageSize, const string& _soundPath, const function<void()>& _callback);
	UIButton(const string& _id, const Vector2f& _position, const Color& _unhoverColor, const Color& _hoverColor, const vector<UIElements*>& _elements, const string& _soundPath, const function<void()>& _callback, const FloatRect& _box);
	~UIButton();

public:
	virtual void Update(const Vector2i& _mousePosition) override;
	virtual vector<Drawable*> GetDrawables() override;
	void ExecuteCallback();
};