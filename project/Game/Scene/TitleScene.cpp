#include "TitleScene.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"
#include "Input.h"

void TitleScene::Init()
{
	sprite = new Sprite();
	sprite->Init(
		{0, 0}, { 1280, 720 },
		{0,0},{1.0f,1.0f,1.0,1.0},
		"Resources/noise1.png");
	titleTex_ = TextureManager::StoreTexture("Resources/noise1.png");
}

void TitleScene::Update()
{
	if(Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		IScene::SetSceneNo(STAGE);
	}
	
	
}
void TitleScene::Draw()
{
	sprite->Draw(titleTex_, { 1.0f,1.0f,1.0,1.0 });
}

void TitleScene::PostDraw()
{
}

void TitleScene::Release() {

}

// ゲームを終了
int TitleScene::GameClose()
{
	return false;
}