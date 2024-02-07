#include "TitleScene.h"
#include "ImGuiCommon.h"
#define _USE_MATH_DEFINES
#include<math.h>

void TitleScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	camera->cameraTransform_.translate = { 0.0f,1.5f,0.0f };
	input = Input::GetInstance();
	room = new Room();
	room->Init();
	car_ = new TitleCar();
	car_->Init();
	
	
}

void TitleScene::Update()
{
	ImGui::Begin("Camera");

	ImGui::DragFloat3("cameratranslation_", &camera->cameraTransform_.translate.x, 0.01f);
	ImGui::DragFloat3("cameratate_", &camera->cameraTransform_.rotate.x, 0.01f);


	ImGui::End();
	sceneTime++;
	if (input->TriggerKey(DIK_SPACE)) {
		sceneNo = CLEAR;
		sceneTime = 0;
	}
	////カメラの更新
	//if(Input::GetInstance()->)
	float theta = (rotate_ / 2.0f) * (float)M_PI;
	Vector2 move = { cosf(theta),sinf(theta) };
	rotate_ += 0.015f;
	Vector3 offset = { 0.00f,0.0f,-10.0f };
	camera->cameraTransform_.rotate.y = rotate_;
	camera->Update();

	offset = TransformNormal(offset, camera->cameraMatrix_);
	camera->cameraTransform_.translate.x = 0 + offset.x;
	camera->cameraTransform_.translate.z = 10 + offset.z;


	car_->Update();

	
	
}
void TitleScene::Draw()
{
	car_->Draw(camera);
	room->Draw(camera);
}

void TitleScene::Release() {
	delete car_;
}

// ゲームを終了
int TitleScene::GameClose()
{
	return false;
}