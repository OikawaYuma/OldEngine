#include "ClearScene.h"

void ClearScene::Init()
{
	input = Input::GetInstance();
}

void ClearScene::Update()
{
	sceneTime++;
	if (input->TriggerKey(DIK_SPACE)) {
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