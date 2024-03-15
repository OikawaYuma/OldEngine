#pragma once
#include "IScene.h"
#include <Sprite.h>

class TitleScene : public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;

private:
	Sprite* demoSprite = nullptr;
	Sprite* demoSprite2 = nullptr;

	//変数
	uint32_t textureHandle;
	uint32_t textureHandle2;
};

