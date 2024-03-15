#include "TitleScene.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"
#include <Input.h>

void TitleScene::Init()
{
	demoSprite = new Sprite();
	demoSprite->Init({ 0.0f,0.0f }, { 600.0f,600.0f }, { 0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f });

	demoSprite2 = new Sprite();
	demoSprite2->Init({ 600.0f,0.0f }, { 600.0f,600.0f }, { 0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f });

	textureHandle = TextureManager::StoreTexture("Resources/uvChecker.png");
	textureHandle2 = TextureManager::StoreTexture("Resources/white.png");
}

void TitleScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo = DEMO;
	}
	demoSprite->Update(textureHandle);
	demoSprite2->Update(textureHandle);
	
}
void TitleScene::Draw()
{
	demoSprite->Draw(textureHandle,{1.0f,1.0f,1.0f,1.0f});
	demoSprite2->Draw(textureHandle2,{1.0f,1.0f,1.0f,1.0f});
}

void TitleScene::Release() {

}

// ゲームを終了
int TitleScene::GameClose()
{
	return false;
}