#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "IScene.h"
#include "TextureManager.h"
#include "Audio.h"

#include "Sprite.h"
class Player 
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(Camera *camera);
	void Release();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ =1;
	uint32_t texture2_ = 1;
	Input* input =nullptr;
	uint32_t soundData;
	uint32_t soundData2;

	Sprite* sprite_ = nullptr;
};

