#include "DemoScene.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"


void DemoScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
	demoSprite = new Sprite();
	demoSprite->Init({0.0f,0.0f},{600.0f,600.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f});
	textureHandle = TextureManager::StoreTexture("Resources/uvChecker.png");

	material.color = { 1.0f,1.0f,1.0f,1.0f };
	material.enableLighting = true;
	worldTransform.Initialize();
	object3d = new Object3d();
	object3d->Init("Resources/box","box.obj",material);
}

void DemoScene::Update()
{
	sceneTime++;
	////カメラの更新
	camera->Update();
	demoSprite->Update(textureHandle);

}
void DemoScene::Draw()
{
	demoSprite->Draw(textureHandle,{1.0f,1.0f,1.0f,1.0f});
	object3d->Draw(worldTransform, textureHandle, camera, material,{0});
}

void DemoScene::Release() {
}

// ゲームを終了
int DemoScene::GameClose()
{
	return false;
}
