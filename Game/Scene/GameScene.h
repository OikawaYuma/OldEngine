#pragma once
#include "IScene.h"
#include "Input.h"
#include "../Car/Car.h"
#include "../Floor/Floor.h"
#include "ImGuiCommon.h"
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
	Camera* camera = nullptr;
	Car* car_ = nullptr;
	Floor* floor_ = nullptr;
};

