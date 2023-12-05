#include "ClearScene.h"

void ClearScene::Init()
{

}

void ClearScene::Update()
{
	sceneTime++;
	if (sceneTime >= 120) {
		sceneNo = TITLE;
		sceneTime = 0;
	}
}
void ClearScene::Draw()
{
	
}

void ClearScene::Release() {

}


// ゲームを終了
int ClearScene::GameClose()
{
	return false;
}