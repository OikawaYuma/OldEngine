#include "Speedpanel.h"
#include "ImGuiCommon.h"
Speedpanel::Speedpanel() {

}
Speedpanel::~Speedpanel() {

}

void Speedpanel::Init(Vector3 translation) {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;
	worldTransform_.scale_ = { 1,1,1 };
	worldTransform_.UpdateMatrix();
	texture_ = TextureManager::StoreTexture("Resources/speedpanel/speedpanel.png");
	model_ = new Model();
	model_->Initialize("Resources/speedpanel", "speedpanel.obj", color,true);
}

void Speedpanel::Update() {
	worldTransform_.UpdateMatrix();
}

void Speedpanel::Draw(Camera* camera) {
	model_->Draw(worldTransform_, texture_, camera, color);
}

void Speedpanel::SetTranslate(Vector3 translation) {

	worldTransform_.translation_ = translation;
}

void Speedpanel::Release()
{
}

