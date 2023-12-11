#pragma once
#include "IScene.h"
#include "Input.h"
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
};
;

