#include "TitleScene.h"
#include "ImGuiCommon.h"


void TitleScene::Init()
{
	input = Input::GetInstance();

	
	
}

void TitleScene::Update()
{
	sceneTime++;
	if (input->TriggerKey(DIK_I)) {
		sceneNo = STAGE;
		sceneTime = 0;
	}

	
}
void TitleScene::Draw()
{
	
}

void TitleScene::Release() {
	
}

// ゲームを終了
int TitleScene::GameClose()
{
	return false;
}