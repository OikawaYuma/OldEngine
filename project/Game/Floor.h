#pragma once
#include "Object3d.h"
#include "WorldTransform.h"
#include "Camera.h"
class Floor
{

public:
	void Init();
	void Update();
	void Draw(Camera* camera);

private:
	std::unique_ptr<Object3d> object_;
	uint32_t floorTex_;
	WorldTransform worldTransform_;
};


