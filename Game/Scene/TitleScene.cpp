#include "TitleScene.h"
#include "ImGuiCommon.h"


void TitleScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	camera->cameraTransform_.translate = { 0.0f,1.5f,0.0f };
	input = Input::GetInstance();

	car_ = new TitleCar();
	car_->Init();

	room_ = new Room();
	room_->Init();
	
}

void TitleScene::Update()
{
	ImGui::Begin("Camera");
	
	ImGui::DragFloat3("cameratranslation_", &camera->cameraTransform_.translate.x, 0.01f, -100.0f, 100.0f);
	
	
	ImGui::End();
	sceneTime++;
	if (input->TriggerKey(DIK_SPACE)) {
		sceneNo = CLEAR;
		sceneTime = 0;
	}
	////カメラの更新
	camera->Update();

	car_->Update();

	
	
}
void TitleScene::Draw()
{
	car_->Draw(camera);
	room_->Draw(camera);
}

void TitleScene::Release() {
	delete car_;
}

// ゲームを終了
int TitleScene::GameClose()
{
	return false;
}