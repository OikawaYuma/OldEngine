#include "Front_left_tire.h"
#include "ImGuiCommon.h"
#define _USE_MATH_DEFINES
#include<math.h>

Front_left_tire::Front_left_tire() {

}

Front_left_tire::~Front_left_tire() {

}

void Front_left_tire::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_.y += 0.05f;
	worldTransform_.translation_.z += 10.0f;
	texture_ = TextureManager::StoreTexture("Resources/uvChecker.png");
	model_ = new Model();
	model_->Initialize("Resources/demo_car", "front_left_tire.obj", color);

	Speed = 10;
}
void Front_left_tire::Update() {

	float theta = (rotate_ / 2.0f) * (float)M_PI;
	Vector2 move = { cosf(theta),sinf(theta) };
	worldTransform_.rotation_.y = theta;
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
	if (input->PushKey(DIK_D) && worldTransform_.rotation_.y <= 1.5f) {
		rotate_ += 0.04f;
	}
	if (worldTransform_.rotation_.y >= 1.5f) {
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.rotation_.y <= -1.5f) {
		worldTransform_.rotation_.y = -1.5f;
	}
	if (input->PushKey(DIK_W)) {
		worldTransform_.translation_.x += Speed * move.y;
		worldTransform_.translation_.z += Speed * move.x;
	}
	worldTransform_.UpdateMatrix();
}

void Front_left_tire::Draw(Camera* camera) {
	model_->Draw(worldTransform_, texture_, camera, color);
}

void Front_left_tire::Release()
{
}