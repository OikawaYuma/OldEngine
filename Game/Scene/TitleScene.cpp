#include "TitleScene.h"
#include "ImGuiCommon.h"


void TitleScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
}

void TitleScene::Update()
{
	sceneTime++;
	if (input->TriggerKey(DIK_SPACE)) {
		sceneNo = STAGE;
		sceneTime = 0;
	}
	////カメラの更新
	camera->Update();
	
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