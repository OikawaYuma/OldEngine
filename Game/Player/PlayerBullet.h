#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Camera.h"
class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Init();
	void Update();
	void Draw();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;

};

