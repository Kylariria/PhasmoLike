#include "Camera.h"
#include "CameraManager.h"
Camera::Camera(const string& _id, const Vector2f& _position, const Vector2f& _size) : IManagable(_id) ,View(_position, _size)
{
	Register();
}

void Camera::Register()
{
	CameraManager::GetInstance().Add(id, this);
}
