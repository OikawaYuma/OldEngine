#include "Skydome.h"

void Skydome::Init()
{
	textureHandle_ = TextureManager::StoreTexture("Resources/uvChecker.png");

	material_.color = {1.0f,1.0f,1.0f,1.0f};
	material_.enableLighting = false;
	worldTransform.Initialize();
	worldTransform.scale_ = { 100.0f,100.0f,100.0f };
	worldTransform.UpdateMatrix();
	//material_.shininess = 5.0f;
	dir_.direction = { 0.0f,-1.0f,0.0f };
	model_ = new Model();
	model_->Initialize("Resources/skydome", "Skydome.obj", material_);
}

void Skydome::Update()
{
	
}
void Skydome::Draw(Camera* camera)
{
	model_->Draw(worldTransform,textureHandle_,camera,material_,dir_);
}

void Skydome::Release()
{
}
