#pragma once

#include "UIElements.h"

using namespace std;

class UIImage : public UIElements
{
	string texturePath;

protected:
	RectangleShape* shape;

public:
	RectangleShape* GetShape() const
	{
		return shape;
	}

	string GetTexturePath() const
	{
		return texturePath;
	}

public:
	UIImage(const string& _id, const Vector2f& _position, const Vector2f& _size, const string& _path);
	~UIImage();

private:
	void Init();
	void InitTexture();
	virtual void Update(const Vector2i& _mousePosition) override;

public:
	virtual vector<Drawable*> GetDrawables() override;
};