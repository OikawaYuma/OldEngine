#pragma once
#include "IScene.h"
#include "Input.h"
#include "../Car/Car.h"
#include "../Floor/Floor.h"
#include "../Car/Front_left_tire/Front_left_tire.h"
#include "../Car/Front_right_tire/Front_right_tire.h"
#include "../Car/Rear_left_tire/Rear_left_tire.h"
#include "../Car/Rear_right_tire/Rear_right_tire.h"
#include "../Skydome/Skydome.h"
#include "../Corn/Corn.h"
#include "../Tree/Tree.h"
#include"CSVReader.h"
#include "ImGuiCommon.h"
#include "Transform.h"
class GameScene :public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;

	void Depart();
	void Accel();

	void LoadCornPopData();
	void UpdateCornPopCommands();
	void CornSpown(Vector3, float);
	void AddCorn(Corn* corn);

private:
	Input* input = nullptr;
	int sceneTime = 0;
	// Carが動く
	bool moveFlag = false;

	bool DriftFlag = false;
	bool AccelFlag = false;

	Corn* corn = nullptr;
	Tree* tree = nullptr;
	Skydome* skydome = nullptr;
	Camera* camera = nullptr;
	Car* car_ = nullptr;
	Transform DriftCamera;
	Transform AccelCamera;
	Transform NormalCamera;
	Transform AccelDriftCamera;
	Floor* floor_ = nullptr;
	Front_left_tire* front_left_tire_ = nullptr;
	Front_right_tire* front_right_tire_ = nullptr;
	Rear_left_tire* rear_left_tire_ = nullptr;
	Rear_right_tire* rear_right_tire_ = nullptr;
	WorldTransform cornTransform = {};

	float cornColLeftX;
	float cornColRightX;
	float cornColBackZ;
	float cornColflontZ;

	float carLeftX;
	float carRightX;
	float carFrontZ;
	float carBackZ;

	Vector3 carPos;
	Vector3 cornPos;
	Vector3 speed;
	// ブロック発生コマンド
	std::stringstream cornPopCommands;
	// ブロック
	std::list<Corn*> corns_;
};

