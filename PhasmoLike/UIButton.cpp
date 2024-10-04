#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"

UIButton::UIButton(const string& _id, const Vector2f& _position, const Color& _unhoverColor, const Color& _hoverColor, const string& _textValue, const int _textSize, const string& _fontPath, const string& _soundPath, const function<void()>& _callback, int* _additionalValue) : UIElements(_id, _position)
{
	unhoverColor = _unhoverColor;
	hoverColor = _hoverColor;
	callback = _callback;
	UIText* _text = new UIText(_id + "Text", _position, _unhoverColor, _textValue, _textSize, _fontPath, false, _additionalValue);
	elements.push_back(_text);
	box = _text->GetText()->getGlobalBounds();
}

UIButton::UIButton(const string& _id, const Vector2f& _position, const Color& _unhoverColor, const Color& _hoverColor, const string& _path, const Vector2f& _imageSize, const string& _soundPath, const function<void()>& _callback) : UIElements(_id, _position)
{
	unhoverColor = _unhoverColor;
	hoverColor = _hoverColor;
	callback = _callback;
	UIImage* _image = new UIImage(_id + "Image", _position, _imageSize, _path);
	elements.push_back(_image);
	box = _image->GetShape()->getGlobalBounds();
}

UIButton::UIButton(const string& _id, const Vector2f& _position, const Color& _unhoverColor, const Color& _hoverColor, const vector<UIElements*>& _elements, const string& _soundPath, const function<void()>& _callback, const FloatRect& _box) : UIElements(_id, _position)
{
	unhoverColor = _unhoverColor;
	hoverColor = _hoverColor;
	callback = _callback;
	elements = _elements;
	box = _box;
}

UIButton::~UIButton()
{
	for (UIElements* _element : elements)
	{
		delete _element;
	}
}

void UIButton::Update(const Vector2i& _mousePosition)
{
	isHover = box.contains(Vector2f(_mousePosition));
	for (UIElements* _element : elements)
	{
		if (UIText* _textElement = dynamic_cast<UIText*>(_element))
		{
			_textElement->GetText()->setFillColor(isHover ? hoverColor : unhoverColor);
			_textElement->Update(_mousePosition);
		}
		else if (UIImage* _imageElement = dynamic_cast<UIImage*>(_element))
		{
			_imageElement->GetShape()->setFillColor(isHover ? hoverColor : unhoverColor);
		}
	}
}

vector<Drawable*> UIButton::GetDrawables()
{
	vector<Drawable*> _drawables;
	for (UIElements* _element : elements)
	{
		if (UIImage* _imageElement = dynamic_cast<UIImage*>(_element))
		{
			_drawables.push_back(_imageElement->GetShape());
		}
	}
	for (UIElements* _element : elements)
	{
		if (UIText* _textElement = dynamic_cast<UIText*>(_element))
		{
			_drawables.push_back(_textElement->GetText());
		}
	}
	return _drawables;
}

void UIButton::ExecuteCallback()
{
	if (callback)
	{
		callback();
	}
}