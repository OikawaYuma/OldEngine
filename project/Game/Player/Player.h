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
	
private:
	std::unique_ptr<Object3d> object_;
	uint32_t platerTex_;
	WorldTransform worldTransform_;
};

