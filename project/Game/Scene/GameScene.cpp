#include "GameScene.h"

#include "ImGuiCommon.h"
void GameScene::Init()
{
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	player_ = std::make_unique<Player>();
	player_->Init();
	player_->SetCamera(camera_.get());
	camera_->SetRotate({ 0.06f, 0.0f, 0.0f });
	flooar_ = new Floor();
	flooar_->Init();
	
	item_ = new Item();
	item_->Init();

	enemy_ = new Enemy();
	enemy_->Init();

	postProcess_ = new PostProcess();
	postProcess_->SetCamera(camera_.get());
	postProcess_->Init();
}

void GameScene::Update()
{
	
	camera_->Update();
	player_->Update();
	flooar_->Update();
	item_->Update();
	enemy_->Update();
	}
void GameScene::Draw()
{
	player_->Draw(camera_.get());
	flooar_->Draw(camera_.get());
	item_->Draw(camera_.get());
	enemy_->Draw(camera_.get());
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

