#pragma once
#include "IScene.h"
#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "../Car/Car.h"
#include "../Floor/Floor.h"
#define STAGE_MAX 10
class ClearScene : public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;
private:
	int sceneTime = 0;
	Input* input = nullptr;

	//メンバ
	Input* input_ = nullptr;
	Camera* camera_ = nullptr;
	Car* car_ = nullptr;
	Floor* floor_ = nullptr;
	Sprite* PushSprite_ = nullptr;
	Sprite* SlectSprite_ = nullptr;
	Model* Stage1model_ = {};
	Model* Stage2model_ = {};
	Model* Stage3model_ = {};
	Vector4 color = { 1,1,1,1 };
	uint32_t texture_ = 1;
	uint32_t PushTexture_ = 1;

	WorldTransform worldTransform_ = {};
	WorldTransform PushTransform_ = {};



	int SelectNumber = 0;
	bool SelectLock = false;

};
;

