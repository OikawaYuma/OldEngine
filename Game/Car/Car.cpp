#include "Car.h"
#include "ImGuiCommon.h"
#include "random"
#define _USE_MATH_DEFINES
#include<math.h>
Car::Car() {

}

Car::~Car() {

}

void Car::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_.y += 0.05f;
	worldTransform_.translation_.z += 10.0f;
	texture_ = TextureManager::StoreTexture("Resources/blue.png");
	texture2_ = TextureManager::StoreTexture("Resources/circle.png");
	model_ = new Model();
	model_->Initialize("Resources/demo_car", "car.obj", color);
	particle = new Particle();
	particle->Initialize();
	Speed = 10;
}

void Car::Update() {
	float theta = (rotate_ / 2.0f) * (float)M_PI;
	move = { cosf(theta),sinf(theta) };
	if (!input->PushKey(DIK_S)) {
		float theta = (rotate_ / 2.0f) * (float)M_PI;
		move = { cosf(theta),sinf(theta) };
		worldTransform_.rotation_.y = theta;
	}
	else if (input->PushKey(DIK_S)) {
		if (rotate_ > 0) {
			float theta = (rotate_ +0.1f / 2.0f) * (float)M_PI;
			move = { cosf(theta),sinf(theta) };
			worldTransform_.rotation_.y = theta;
		}
		else if (rotate_ < 0) {
			float theta = (rotate_ - 0.1f / 2.0f) * (float)M_PI;
			move = { cosf(theta),sinf(theta) };
			worldTransform_.rotation_.y = theta;
		}
		
	}

	//worldTransform_.translation_.z += Speed;
	if (input->PushKey(DIK_LSHIFT)) {
		Speed = ShiftSpeed;
	}
	else
	{
		Speed = NormalSpeed;
	}
	if (worldTransform_.translation_.x >= 100.0f) {
		worldTransform_.translation_.x = 100.0f;
	}
	if (worldTransform_.translation_.x <= -100.0f) {
		worldTransform_.translation_.x = -100.0f;
	}

	if (input->PushKey(DIK_A) && worldTransform_.rotation_.y >= -1.5f) {
		rotate_ -= 0.04f;
	}
	else if (input->PushKey(DIK_D) && worldTransform_.rotation_.y <= 1.5f) {
		rotate_ += 0.04f;
	}
	/*else {
		if (rotate_ > 0) {
			rotate_ -= 0.01f;
			if (rotate_ < 0) {
				rotate_ = 0;
			}
		}
		else if (rotate_ < 0) {
			rotate_ += 0.01f;
			if (rotate_ > 0) {
				rotate_ = 0;
			}
		}
	}*/

	

	if (worldTransform_.rotation_.y >= 1.5f) {
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.rotation_.y <= -1.5f) {
		worldTransform_.rotation_.y = -1.5f;
	}
	if (input->TriggerKey(DIK_W)) {
		moveFlag_ = true;
	}
	
	if (moveFlag_ && input->PushKey(DIK_S)) {
		worldTransform_.translation_.x += DriftSpeed  * move.y;
		worldTransform_.translation_.z += DriftSpeed * move.x;
	}
	else if (moveFlag_) {
		worldTransform_.translation_.x += Speed * move.y;
		worldTransform_.translation_.z += Speed * move.x;

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
	particle->Draw({worldTransform_.translation_.x - 3 * move.y,worldTransform_.translation_.y,worldTransform_.translation_.z -3  * move.x }, texture2_, camera);
	//sprite_->Draw(texture_,color);
}

void Car::Release()
{
	
}
