#include "Floor.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Model.h"
void Floor::Init()
{
	floorTex_ = TextureManager::GetInstance()->StoreTexture("Resources/uvChecker.png");
	worldTransform_.Initialize();
	worldTransform_.scale_.x = 1000.0f;
	worldTransform_.scale_.z = 1000.0f;
	worldTransform_.translation_.y = -1.0f;

	//ModelManager::GetInstance()->LoadModel("Resources/box/", "box.obj");
	object_ = std::make_unique<Object3d>();
	object_->Init();
	object_->SetModel("box.obj");




}

void Floor::Update()
{
	object_->Update();

	worldTransform_.UpdateMatrix();
	object_->SetWorldTransform(worldTransform_);
}

void Floor::Draw(Camera* camera)
{
	object_->Draw(floorTex_, camera);
}

