#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Input.h"
#include "Particle.h"
#include "TextureManager.h"
class TitleScene : public IScene
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
	uint32_t textureHandle;
	uint32_t textureHandle2;
	uint32_t textureHandle3;
	Sprite* sprite_ = nullptr;
	Sprite* title_ = nullptr;
	Sprite* push_ = nullptr;
	float fadeColor_ = 1.0f;
	float pushColor_ = 1.0f;
	bool pushFlag = false;
	bool sceneChange = false;
	bool startFlag_ = false;
};

