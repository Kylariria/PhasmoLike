#pragma once
#include "IManager.h"
#include "Camera.h"
#include "Singleton.h"


class CameraManager : public IManager<string,Camera> , public Singleton<CameraManager>
{
public:
	Camera* InitMainCamera(const string& _id,const Vector2f& _position, const Vector2f& _size);
};

