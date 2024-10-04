#include "CameraManager.h"

Camera* CameraManager::InitMainCamera(const string& _id, const Vector2f& _position, const Vector2f& _size)
{
    return new Camera(_id,_position,_size);
}
