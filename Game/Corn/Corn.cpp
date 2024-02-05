#include "Corn.h"
#include "ImGuiCommon.h"
Corn::Corn() {

}
Corn::~Corn() {

}

void Corn::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	texture_ = TextureManager::StoreTexture("Resources/corn/corn.png");
	model_ = new Model();
	model_->Initialize("Resources/corn", "corn.obj", color);
	worldTransform_.translation_.z = 600.0f;
}

void Corn::Update() {
	worldTransform_.UpdateMatrix();
}

void Corn::Draw(Camera* camera) {
	model_->Draw(worldTransform_, texture_, camera, color);
}

void Corn::Release()
{
}

