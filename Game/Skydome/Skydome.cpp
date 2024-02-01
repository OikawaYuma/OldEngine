#include "Skydome.h"

Skydome::Skydome() {

}

Skydome::~Skydome() {

}

void Skydome::Init() {
	worldTransform_.Initialize();
	worldTransform_.translation_.y += 0.05f;
	worldTransform_.translation_.z += 10.0f;
	texture_ = TextureManager::StoreTexture("Resources/demo_car/CAR.png");
}

void Skydome::Update() {

	worldTransform_.UpdateMatrix();

}

void Skydome::Draw(Camera* camera) {
	sphere_->Draw()
}

void Skydome::Release()
{

}
