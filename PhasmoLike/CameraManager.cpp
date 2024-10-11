#include "CameraManager.h"

Camera* CameraManager::InitMainCamera(const string& _id, const Vector2f& _position, const Vector2f& _size)
{
    mainCamera = new Camera(_id, _position, _size);
    return mainCamera;
}
