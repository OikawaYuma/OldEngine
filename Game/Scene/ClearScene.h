#pragma once
#include "IScene.h"
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"
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
	Sprite* sprite_ = nullptr;
	float fadeColor_ = 1.0f;
	uint32_t textureHandle_;
	bool startFlag_ = false;
	bool sceneChange = false;
};
;

