#pragma once
#include "IScene.h"
#include "Sprite.h"
class TitleScene : public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void PostDraw()override;
	void Release()override;
	int GameClose()override;

private:
	Sprite* sprite = nullptr;
	uint32_t titleTex_;
};

