#include "DemoScene.h"
#include "ImGuiCommon.h"


void DemoScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
}

void DemoScene::Update()
{
	sceneTime++;
	////カメラの更新
	camera->Update();

}
void DemoScene::Draw()
{
}

void DemoScene::Release() {
}

// ゲームを終了
int DemoScene::GameClose()
{
	return false;
}
