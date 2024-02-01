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
	texture_ = TextureManager::StoreTexture("Resources/demo_car/CAR.png");
	texture2_ = TextureManager::StoreTexture("Resources/circle.png");
	texture3_ = TextureManager::StoreTexture("Resources/cubeRED.png");
	model_ = new Model();
	model_->Initialize("Resources/demo_car", "CAR.obj", color);

	Speed = 10;
	rearLeft = {
		{-0.9f,-0.7f},
		{0.1f,0.4f},
		{-0.5f,0.3f}
	};

	rearRight = {
		{0.7f,0.9f},
		{0.1f,0.4f},
		{-0.5f,0.3f}
	};

	particle = new Particle();
	particle->Initialize();
	particle2 = new Particle();
	particle2->Initialize();
	particle3 = new Particle();
	particle3->Initialize();
	particle4 = new Particle();
	particle4->Initialize();
}

void Car::Update() {

	//if(Input::GetInstance()->)
	float theta = (rotate_ / 2.0f) * (float)M_PI;
	move = { cosf(theta),sinf(theta) };
	worldTransform_.rotation_.y = theta;
	Drift();
	{

	}

	//worldTransform_.translation_.z += Speed;
	/*if (input->PushKey(DIK_LSHIFT)) {
		Speed = ShiftSpeed;
	}*/
	/*else
	{
		Speed = NormalSpeed;
	}*/
	if (worldTransform_.translation_.x >= 100.0f) {
		worldTransform_.translation_.x = 100.0f;
	}
	if (worldTransform_.translation_.x <= -100.0f) {
		worldTransform_.translation_.x = -100.0f;
	}

	Move();
	Accel();
	if (input->PushKey(DIK_A) && worldTransform_.rotation_.y >= -1.5f) {
		rotate_ -= 0.04f;
	}
	else if (input->PushKey(DIK_D) && worldTransform_.rotation_.y <= 1.5f) {
		rotate_ += 0.04f;
	}
	if (worldTransform_.rotation_.y >= 1.5f) {
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.rotation_.y <= -1.5f) {
		worldTransform_.rotation_.y = -1.5f;
	}
	if (input->TriggerKey(DIK_W)) {
		moveFlag_ = true;
	}
	{
		Depart();
	}

	worldTransform_.UpdateMatrix();

	ImGui::Begin("Demo_Car");
	ImGui::DragFloat3("translation_", (float*)&worldTransform_.translation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("rotation_", (float*)&worldTransform_.rotation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("scale_", (float*)&worldTransform_.scale_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat4("color", &color.x, 0.01f);
	ImGui::Text("%f", theta);
	ImGui::Text("%f", rotate_);
	ImGui::End();
	//Audio::SoundLoopWave(Audio::GetIXAudio().Get(), soundData);
}

void Car::Draw(Camera* camera) {
	switch (driveMode_) {
	case NormalMode: {
		model_->Draw(worldTransform_, texture_, camera, color);
		if (input->PushKey(DIK_LSHIFT)) {
			particle3->Draw({ worldTransform_.translation_.x - 3 * move.y,worldTransform_.translation_.y+0.3f,worldTransform_.translation_.z - 3 * move.x }, texture3_, camera, rearLeft);
			particle4->Draw({ worldTransform_.translation_.x - 3 * move.y,worldTransform_.translation_.y+0.3f,worldTransform_.translation_.z - 3 * move.x }, texture3_, camera, rearRight);
		
		}
		break;
	}
	case DriftMode: {
		WorldTransform driftWT = worldTransform_;
		if (rotate_ > 0) {
			driftWT.rotation_.y = worldTransform_.rotation_.y + 0.2f;
		}
		else if (rotate_ < 0) {
			driftWT.rotation_.y = worldTransform_.rotation_.y - 0.2f;
		}
		driftWT.UpdateMatrix();
		float theta = (rotate_ / 2.0f) * (float)M_PI;
		Vector2 move2 = { cosf(theta),sinf(theta) };
		model_->Draw(driftWT, texture_, camera, color);
		particle->Draw({ driftWT.translation_.x - 2 * move2.y,driftWT.translation_.y-0.2f,driftWT.translation_.z - 2 * move2.x }, texture2_, camera, rearLeft);
		particle2->Draw({ driftWT.translation_.x - 2 * move2.y,driftWT.translation_.y-0.2f,driftWT.translation_.z - 2 * move2.x }, texture2_, camera, rearRight);
		break;
	}
	}
	//sprite_->Draw(texture_,color);
}

void Car::Release()
{

}

// 車の発車
void Car::Depart()
{
	XINPUT_STATE Gamepad{};
	/*if (!Input::GetInstance()->GetJoystickState(Gamepad)) {
		return;
	}*/
	if (Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

		moveFlag_ = true;

	}

	else {

	}
}

void Car::Move()
{
	XINPUT_STATE joyState{};
	/*switch (driveMode_) {
	}*/
	//if (Input::GetInstance()->GetJoystickState(joyState)) {

		if (worldTransform_.rotation_.y > 1.5f) {
			worldTransform_.rotation_.y = 1.5f;
			rotate_ = 0.96f;
		}
		if (worldTransform_.rotation_.y < -1.5f) {
			worldTransform_.rotation_.y = -1.5f;
			rotate_ = -0.96f;
		}
		switch (driveMode_) {
		case NormalMode: {
			// 回転
			if (worldTransform_.rotation_.y >= -1.5f && worldTransform_.rotation_.y <= 1.5f) {
				rotate_ += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 0.04f;

			}
			// 移動
			if (moveFlag_) {
				worldTransform_.translation_.x += Speed * move.y;
				worldTransform_.translation_.z += Speed * move.x;

			}
			worldTransform_.rotation_.z = 0.0f; 
			worldTransform_.rotation_.x = 0.0f;
			break;
		}
		case DriftMode: {
			// 回転
			/*if (worldTransform_.rotation_.y >= -1.5f && worldTransform_.rotation_.y <= 1.5f) {
				rotate_ += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 0.06f;

			}*/


			if (rotate_ >= 0.05f) {
				short leftStickX = joyState.Gamepad.sThumbLX;
				if (leftStickX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
					rotate_ += 0.01f;
					
				}
				else if (leftStickX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
					rotate_ -= 0.005f;
					worldTransform_.translation_.x -=1.5f * move.y;
					
					//worldTransform_.translation_.z -= 1.5f * move.x;
				}
				
				if (rotate_ < 0.05f) {
					rotate_ = 0.05f;
				}
				worldTransform_.rotation_.z = -0.05f;
				worldTransform_.rotation_.x = -0.05f;
			}
			else if (rotate_ <= -0.05f) {

				short leftStickX = joyState.Gamepad.sThumbLX;
				if (leftStickX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
					rotate_ -= 0.01f;
				}
				else if (leftStickX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
					rotate_ += 0.005f;
					worldTransform_.translation_.x -= 1.5f * move.y;
					//worldTransform_.translation_.z -= 1.5f * move.x;
				}
				//rotate_ += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * 0.06f;
				if (rotate_ > -0.05f) {
					rotate_ = -0.05f;
				}
				worldTransform_.rotation_.z = 0.05f;
				worldTransform_.rotation_.x = -0.05f;
			}
			


			// 移動
			if (moveFlag_) {
				worldTransform_.translation_.x += DriftSpeed * move.y;
				worldTransform_.translation_.z += DriftSpeed * move.x;
			}

			break;
		}
		}
		//rotate_ += 0.04f;

	}
//}

void Car::Drift()
{
	XINPUT_STATE joyState{};
	/*if (!Input::GetInstance()->GetJoystickState(joyState)) {
		return;
	}*/
	if (!input->PushKey(DIK_S) && !(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) {

		driveMode_ = NormalMode;
	}
	else if (input->PushKey(DIK_S) || (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) &&!(rotate_<0.05f&& rotate_>-0.05)) {
		driveMode_ = DriftMode;
		/*if (rotate_ > 0) {
			float theta = (rotate_ + 0.1f / 2.0f) * (float)M_PI;
			move = { cosf(theta),sinf(theta) };
			worldTransform_.rotation_.y = theta;
		}
		else if (rotate_ < 0) {
			float theta = (rotate_ - 0.1f / 2.0f) * (float)M_PI;
			move = { cosf(theta),sinf(theta) };
			worldTransform_.rotation_.y = theta;
		}*/

	}

}

void Car::Accel()
{
	XINPUT_STATE joyState{};
	/*if (!Input::GetInstance()->GetJoystickState(joyState)) {
		return;
	}*/

	if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || Input::GetInstance()->PushKey(DIK_LSHIFT)) {
		Speed = ShiftSpeed;
	}
	else
	{
		Speed = NormalSpeed;
	}

}

