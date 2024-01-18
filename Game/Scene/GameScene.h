#pragma once
#include "IScene.h"
#include "Input.h"
#include "../Car/Car.h"
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
	float Speed = 0.0f;
	float NormalSpeed = 1.0f;
	float ShiftSpeed = 2.0f;
};

