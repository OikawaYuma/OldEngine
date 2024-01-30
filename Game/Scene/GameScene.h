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
#include"../../Colision.h"
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
	bool isColision = false;
	int sceneTime = 0;
	// Carが動く
	bool moveFlag = false;
	Camera* camera = nullptr;
	Car* car_ = nullptr;
	Floor* floor_ = nullptr;
	Front_left_tire* front_left_tire_ = nullptr;
	Front_right_tire* front_right_tire_ = nullptr;
	Rear_left_tire* rear_left_tire_ = nullptr;
	Rear_right_tire* rear_right_tire_ = nullptr;
	Model* collisionModel_ = nullptr;
	uint32_t texture_ = {};
	uint32_t texture2_ = {};
	Vector4 color;
	WorldTransform colisionTransform_ = {};
	Colision* colision_ = nullptr;
	Model* GreenModel = nullptr;
	WorldTransform GreenWorldTransform_;


};

