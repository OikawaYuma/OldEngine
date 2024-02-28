#include "DemoScene.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"


void DemoScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
	demoSprite = new Sprite();
	demoSprite->Init({0.0f,0.0f},{100.0f,100.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f});
	textureHandle = TextureManager::StoreTexture("Resources/uvChecker.png");
}

void DemoScene::Update()
{
	sceneTime++;
	////カメラの更新
	camera->Update();

}
void DemoScene::Draw()
{
	demoSprite->Draw(textureHandle,{1.0f,1.0f,1.0f,1.0f});
}

void DemoScene::Release() {
}

// ゲームを終了
int DemoScene::GameClose()
{
	return false;
}
