#pragma once
#include "Object3d.h"
#include "WorldTransform.h"
#include "Camera.h"
class Item
{

public:
	void Init();
	void Update();
	void Draw(Camera* camera);

private:
	std::unique_ptr<Object3d> object_;
	std::unique_ptr<Object3d> object_1;
	std::unique_ptr<Object3d> object_2;
	std::unique_ptr<Object3d> object_3;
	std::unique_ptr<Object3d> object_4;
	uint32_t floorTex_;
	WorldTransform worldTransform_;
	WorldTransform worldTransform_1;
	WorldTransform worldTransform_2;
	WorldTransform worldTransform_3;
	WorldTransform worldTransform_4;


};
