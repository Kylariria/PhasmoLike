#include "CustomWindow.h"
#include "WindowManager.h"
#include "WindowManager.h"

CustomWindow::CustomWindow(const string& _name) : IManagable(_name)
{
	Register();
}

void CustomWindow::Register()
{
	WindowManager::GetInstance().Add(id,this);
}
