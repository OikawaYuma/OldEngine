#pragma once
#include "Camera.h"
#include "WorldTransform.h"
#include "Input.h"
class RailCamera
{
public:
	void Init(const Vector3& pos,const Vector3& rot);
	void Update();
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	Camera* camera = nullptr;
private:
	WorldTransform worldTransform_;
	
	Input* input_ = nullptr;
};

