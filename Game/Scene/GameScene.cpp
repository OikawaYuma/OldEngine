#include "GameScene.h"

void GameScene::Init()
{


}

void GameScene::Update()
{

	sceneTime++;
	if (sceneTime >= 120) {
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
