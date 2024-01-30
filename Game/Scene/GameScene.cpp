#include "GameScene.h"

void GameScene::Init()
{
	input = Input::GetInstance();
	camera = new Camera;
	camera->Initialize();

	player_ = new Player();
	player_->Init();
	
	enemy_ = new Enemy();
	enemy_->Init();

}

void GameScene::Update()
{

	sceneTime++;
	if (input->TriggerKey(DIK_I)) {
		sceneNo = CLEAR;
		sceneTime = 0;
	}

	////カメラの更新
	camera->Update();

	player_->Update();
	enemy_->Update();

}
void GameScene::Draw()
{
	player_->Draw(camera);
	enemy_->Draw(camera);
}

void GameScene::Release() {
	delete player_;
	delete enemy_;
}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}
