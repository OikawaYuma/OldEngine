#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "Camera.h"

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(Camera *camera);
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ =1;
	
};

