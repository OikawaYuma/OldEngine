#include "GameScene.h"

void GameScene::Init()
{
	
	player_ = std::make_unique<Player>();
	player_->Init();
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();

	postProcess_ = new PostProcess();
	postProcess_->SetCamera(camera_.get());
	postProcess_->Init();
}

void GameScene::Update()
{
	player_->Update();
}
void GameScene::Draw()
{
	player_->Draw(camera_.get());
}

void GameScene::PostDraw()
{
	postProcess_->Draw();
	
}

void GameScene::Release() {

}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}

