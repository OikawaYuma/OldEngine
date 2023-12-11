#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "IScene.h"
#include "TextureManager.h"
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
	uint32_t texture2_ = 1;
	Input* input =nullptr;
	
};

