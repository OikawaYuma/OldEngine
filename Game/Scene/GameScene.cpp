#include "GameScene.h"

void GameScene::Init()
{
	input = Input::GetInstance();

}

void GameScene::Update()
{

	sceneTime++;
	if (input->TriggerKey(DIK_I)) {
		sceneNo = CLEAR;
		sceneTime = 0;
	}
	

}
void GameScene::Draw()
{
	
}

void GameScene::Release() {

}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}
