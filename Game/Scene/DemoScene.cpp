#include "DemoScene.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"
#include "ModelManager.h"

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
	worldTransform2.Initialize();
	worldTransform2.translation_.x = 5;
	worldTransform2.UpdateMatrix();

	ModelManager::GetInstance()->LoadModel("Resources/box", "box.obj");
	ModelManager::GetInstance()->LoadModel("Resources/ball", "ball.obj");
	object3d = new Object3d();
	object3d->Init();
	object3d2 = new Object3d();
	object3d2->Init();
	
	object3d->SetModel("box.obj");
	object3d2->SetModel("ball.obj");
}

void DemoScene::Update()
{
	sceneTime++;
	////カメラの更新
	camera->Update();
	demoSprite->Update(textureHandle);

	object3d->SetWorldTransform(worldTransform);
	object3d2->SetWorldTransform(worldTransform2);

	object3d->Update();
	object3d2->Update();

}
void DemoScene::Draw()
{
	demoSprite->Draw(textureHandle,{1.0f,1.0f,1.0f,1.0f});
	object3d->Draw(textureHandle,camera);
	object3d2->Draw(textureHandle, camera);
}

void DemoScene::Release() {
}

// ゲームを終了
int DemoScene::GameClose()
{
	return false;
}
