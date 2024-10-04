#include "UIElements.h"
#include "Menu.h"

UIElements::UIElements(const string& _id, const Vector2f& _position) : IManagable(_id), position(_position)
{
}

void UIElements::Register()
{
	owner->Add(id, this);
}
