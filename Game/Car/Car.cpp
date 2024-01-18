#include "Car.h"
#include "ImGuiCommon.h"
Car::Car() {

}

Car::~Car() {

}

void Car::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	texture_ = TextureManager::StoreTexture("Resources/uvChecker.png");
	model_ = new Model();
	model_->Initialize("Resources/demo_car", "demo_car.obj", color);
}

void Car::Update() {
	//worldTransform_.translation_.z += Speed;
	if (input->PushKey(DIK_LSHIFT)) {
		Speed = ShiftSpeed;
	}
	else
	{
		Speed = NormalSpeed;
	}
	if (input->PushKey(DIK_W)) {
		worldTransform_.translation_.z += Speed;
	}
	if (input->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= Speed;
	}
	if (input->PushKey(DIK_D)) {
		worldTransform_.translation_.x += Speed;
	}
	if (input->PushKey(DIK_S)) {
		worldTransform_.translation_.z -= Speed * 2;
	}
	worldTransform_.UpdateMatrix();
	ImGui::Begin("Demo_Car");
	ImGui::DragFloat3("translation_", (float*)&worldTransform_.translation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("rotation_", (float*)&worldTransform_.rotation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("scale_", (float*)&worldTransform_.scale_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat4("color", &color.x, 0.01f);
	ImGui::Text("Shift & WASD = Dash");
	ImGui::End();
	//Audio::SoundLoopWave(Audio::GetIXAudio().Get(), soundData);
}

void Car::Draw(Camera* camera) {
	model_->Draw(worldTransform_, texture_, camera, color);
	//sprite_->Draw(texture_,color);
}

void Car::Release()
{
}
