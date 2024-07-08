#pragma once
#include "Object3d.h"
#include "WorldTransform.h"
#include "Camera.h"
class Player
{
public:
	void Init();
	void Update();
	void Draw(Camera* camera);
	void SetCamera(Camera* camera) { camera_ = camera; };
	
private:
	std::unique_ptr<Object3d> object_;
	uint32_t floorTex_;
	WorldTransform worldTransform_;
	Camera* camera_ = nullptr;
	bool isJump_ = false;
	float accel_ = 0;
	Vector3 cameraToPlayerDistance_{0.0f, 6.9f, -44.0f};
};

