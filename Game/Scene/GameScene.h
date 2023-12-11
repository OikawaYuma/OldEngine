#pragma once
#include "IScene.h"
#include "Input.h"
class GameScene :public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;
private:
	Input* input = nullptr;
	int sceneTime = 0;
};

