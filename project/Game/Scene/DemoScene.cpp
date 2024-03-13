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
	textureHandle2 = TextureManager::StoreTexture("Resources/white.png");

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
	particle = new Particle();
	particle2 = new Particle();

	demoRandPro = {
		{1.0f,4.0f},
		{1.0f,4.0f},
		{0.0f,2.0f}
	};

	demoEmitter_.count = 6;
	demoEmitter_.frequency = 0.02f;
	demoEmitter_.frequencyTime = 0.0f;
	demoEmitter_.transform.scale = { 0.5f,0.5f,0.5f };
	particle->Initialize(demoEmitter_);
	particle2->Initialize(demoEmitter_);
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
	//demoSprite->Draw(textureHandle,{1.0f,1.0f,1.0f,1.0f});
	//object3d->Draw(textureHandle,camera);
	//object3d2->Draw(textureHandle2, camera);
	particle->Draw(demoEmitter_, { worldTransform.translation_.x,worldTransform.translation_.y,worldTransform.translation_.z}, textureHandle, camera, demoRandPro, false);
	particle2->Draw(demoEmitter_, { worldTransform2.translation_.x,worldTransform2.translation_.y,worldTransform2.translation_.z }, textureHandle2, camera, demoRandPro, false);
}

void DemoScene::Release() {
}

// ゲームを終了
int DemoScene::GameClose()
{
	return false;
}
