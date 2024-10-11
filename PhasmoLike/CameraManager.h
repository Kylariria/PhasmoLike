#pragma once
#include "IManager.h"
#include "Camera.h"
#include "Singleton.h"


class CameraManager : public IManager<string,Camera> , public Singleton<CameraManager>
{
	Camera* mainCamera = nullptr;
public:
	Camera* InitMainCamera(const string& _id,const Vector2f& _position, const Vector2f& _size);

	inline Camera* GetMainCamera() { return mainCamera; }
};

