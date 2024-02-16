#pragma once
#include "Camera.h"
#include "WorldTransform.h"
class RailCamera
{
public:
	void Init();
	void Update();
private:
	WorldTransform worldTransform_;
	Camera* camera = nullptr;
};

