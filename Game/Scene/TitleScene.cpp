#include "TitleScene.h"
#include "ImGuiCommon.h"


void TitleScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();

	player_ = new Player();
	player_->Init();

	
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

	player_->Update();
	
}
void TitleScene::Draw()
{
	player_->Draw(camera);
}

void TitleScene::Release() {
	delete player_;
}

// ゲームを終了
int TitleScene::GameClose()
{
	return false;
}