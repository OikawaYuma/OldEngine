#include "GameScene.h"

#include "ImGuiCommon.h"
void GameScene::Init()
{
	camera_ = new Camera();
	camera_->Initialize();
	player_ = new Player();
	player_->Init();
	player_->SetCamera(camera_);
	camera_->SetRotate({ 0.05f, 0.0f, 0.0f });
	flooar_ = new Floor();
	flooar_->Init();

	postProcess_ = new PostProcess();
	postProcess_->SetCamera(camera_);
	postProcess_->Init();
}

void GameScene::Update()
{
	Vector3 camerarotate_ = camera_->GetRotate();
	ImGui::Begin("Camera");
	ImGui::DragFloat3("rotate", &camerarotate_.x,0.01f);
	ImGui::End();
	camera_->SetRotate(camerarotate_);
	camera_->Update();
	player_->Update();
	flooar_->Update();
}
void GameScene::Draw()
{
	player_->Draw(camera_);
	flooar_->Draw(camera_);
}

void GameScene::PostDraw()
{
	postProcess_->Draw();
	
}

void GameScene::Release() {
	postProcess_->Release();
}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}

