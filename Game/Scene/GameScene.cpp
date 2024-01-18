#include "GameScene.h"

void GameScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
	car_ = new Car();
	car_->Init();
}

void GameScene::Update()
{

	sceneTime++;
	if (input->TriggerKey(DIK_SPACE)) {
		sceneNo = CLEAR;
		sceneTime = 0;
	}
	camera->Update();

	car_->Update();
}
void GameScene::Draw()
{
	car_->Draw(camera);
}

void GameScene::Release() {
	delete car_;
}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}
