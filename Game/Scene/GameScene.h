#pragma once
#include "IScene.h"
#include "Input.h"
#include "../Car/Car.h"
#include "../Floor/Floor.h"
#include "../Car/Front_left_tire/Front_left_tire.h"
#include "../Car/Front_right_tire/Front_right_tire.h"
#include "../Car/Rear_left_tire/Rear_left_tire.h"
#include "../Car/Rear_right_tire/Rear_right_tire.h"
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
	Front_left_tire* front_left_tire_ = nullptr;
	Front_right_tire* front_right_tire_ = nullptr;
	Rear_left_tire* rear_left_tire_ = nullptr;
	Rear_right_tire* rear_right_tire_ = nullptr;
};

