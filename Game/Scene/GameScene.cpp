#include "GameScene.h"

void GameScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
	car_ = new Car();
	car_->Init();
	floor_ = new Floor();
	floor_->Init();
}

void GameScene::Update()
{
	sceneTime++;
	if (input->PushKey(DIK_W)) {
		camera->cameraTransform_.translate.z += car_->Speed;
	}
	if (input->TriggerKey(DIK_SPACE)) {
		sceneNo = CLEAR;
		sceneTime = 0;
	}
	
	

	if (input->PushKey(DIK_LSHIFT)) {
		camera->cameraTransform_.scale.x = 2.0f;
		camera->cameraTransform_.scale.y = 2.0f;
		camera->cameraTransform_.scale.z = 0.6f;
	}
	else
	{
		camera->cameraTransform_.translate.z = car_->GetWorldTransform().z - 20;
		camera->cameraTransform_.translate.y = 5.0f;
	    camera->cameraTransform_.rotate.x = 0.15f;
		camera->cameraTransform_.scale.x = 1.0f;
		camera->cameraTransform_.scale.y = 1.0f;
		camera->cameraTransform_.scale.z = 1.0f;
	}
	camera->Update();
	floor_->Update();
	car_->Update();
	ImGui::Begin("Camera");
	//ImGui::DragFloat3("Translate", &camera->cameraTransform_.translate.x, camera->cameraTransform_.translate.y, camera->cameraTransform_.translate.z, 1.0f);
	ImGui::DragFloat3("Translate", (float*)&camera->cameraTransform_.translate, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Rotate", (float*)&camera->cameraTransform_.rotate, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Scale", (float*)&camera->cameraTransform_.scale, 0.01f, -100.0f, 100.0f);
	ImGui::End();
}
void GameScene::Draw()
{
	floor_->Draw(camera);
	car_->Draw(camera);
}

void GameScene::Release() {
	delete floor_;
	delete car_;
}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}
