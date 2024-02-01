#include "GameScene.h"
#define _USE_MATH_DEFINES
#include<math.h>

void GameScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
	car_ = new Car();
	car_->Init();
	floor_ = new Floor();
	floor_->Init();
	front_left_tire_ = new Front_left_tire();
	front_left_tire_->Init();
	front_right_tire_ = new Front_right_tire();
	front_right_tire_->Init();
	rear_left_tire_ = new Rear_left_tire();
	rear_left_tire_->Init();
	rear_right_tire_ = new Rear_right_tire();
	rear_right_tire_->Init();

	DriftCamera.rotate.x = 0.125f;
	AccelCamera;
	NormalCamera.rotate.x = 0.125f;
	AccelDriftCamera;
}

void GameScene::Update()
{
	float theta = (car_->rotate_ / 2.0f) * (float)M_PI;
	Vector2 move = { cosf(theta),sinf(theta) };
	car_->worldTransform_.rotation_.y = theta;
	camera->cameraTransform_.translate.x = car_->worldTransform_.translation_.x;
	camera->cameraTransform_.rotate.y = car_->worldTransform_.rotation_.y / 10;
	camera->cameraTransform_.rotate.z = camera->cameraTransform_.rotate.y;
	sceneTime++;
	if (input->TriggerKey(DIK_W)) {
		moveFlag = true;
	}
	
	if (input->TriggerKey(DIK_SPACE)) {
		sceneNo = TITLE;
		sceneTime = 0;
	}
	if (camera->cameraTransform_.rotate.y <= -0.15f) {
		camera->cameraTransform_.rotate.y = -0.15f;
	}
	if (camera->cameraTransform_.rotate.y >= 0.15f) {
		camera->cameraTransform_.rotate.y = 0.15f;
	}

	Depart();
	Accel();
	camera->Update();
	floor_->Update();
	car_->Update();
	front_left_tire_->Update();
	front_right_tire_->Update();
	rear_left_tire_->Update();
	rear_right_tire_->Update();
	ImGui::Begin("Camera");
	ImGui::Text("NormalCamera");
	ImGui::DragFloat3("NScale",&NormalCamera.scale.x);
	ImGui::DragFloat3("NRotate", &NormalCamera.rotate.x);
	ImGui::DragFloat3("NTranslate", &NormalCamera.translate.x);

	ImGui::Text("AccelCamera");
	ImGui::DragFloat3("AScale", &AccelCamera.scale.x);
	ImGui::DragFloat3("ARotate", &AccelCamera.rotate.x);
	ImGui::DragFloat3("ATranslate", &AccelCamera.translate.x);

	ImGui::Text("DriftCamera");
	ImGui::DragFloat3("DScale", &DriftCamera.scale.x);
	ImGui::DragFloat3("DRotate", &DriftCamera.rotate.x);
	ImGui::DragFloat3("DTranslate", &AccelCamera.translate.x);

	ImGui::Text("AccelDriftCamera");
	ImGui::DragFloat3("ADScale", &AccelDriftCamera.scale.x);
	ImGui::DragFloat3("ADRotate", &AccelDriftCamera.rotate.x);
	ImGui::DragFloat3("ADTranslate", &AccelDriftCamera.translate.x);

	ImGui::Checkbox("Aceel",&AccelFlag);
	ImGui::Checkbox("Drift", &DriftFlag);
	ImGui::End();
}
void GameScene::Draw()
{
	floor_->Draw(camera);
	car_->Draw(camera);
	/*front_left_tire_->Draw(camera);
	front_right_tire_->Draw(camera);
	rear_left_tire_->Draw(camera);
	rear_right_tire_->Draw(camera);*/
}
void GameScene::Release() {
	delete floor_;
	delete front_left_tire_;
	delete front_right_tire_;
	delete rear_left_tire_;
	delete rear_right_tire_;
	delete car_;
}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}

// 車の発車
void GameScene::Depart()
{
	XINPUT_STATE Gamepad{};
	/*if (!Input::GetInstance()->GetJoystickState(Gamepad)) {
		return;
	}*/
	if (Gamepad.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

		moveFlag = true;

	}

	else {

	}



}



void GameScene::Accel(){
	XINPUT_STATE joyState{};
	float theta = (car_->rotate_ / 2.0f) * (float)M_PI;
	Vector2 move = { cosf(theta),sinf(theta) };
	/*if (!Input::GetInstance()->GetJoystickState(joyState)) {
		return;
	}*/
	switch (car_->GetDriveMode())
	{
	case NormalMode: {

		//camera->cameraTransform_.rotate = AccelCamera.rotate;
		//camera->cameraTransform_.translate = AccelCamera.translate;
		if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || input->PushKey(DIK_LSHIFT) || AccelFlag) {
			if (camera->cameraTransform_.scale.x <= 2.0f) {
				camera->cameraTransform_.scale.x += 0.05f;
			}
			if (camera->cameraTransform_.scale.y <= 2.0f) {
				camera->cameraTransform_.scale.y += 0.05f;
			}
			if (camera->cameraTransform_.scale.z >= 0.6f) {
				camera->cameraTransform_.scale.z -= 0.02f;
			}
			/*camera->cameraTransform_.scale.x = 2.0f;
			camera->cameraTransform_.scale.y = 2.0f;
		camera->cameraTransform_.scale.z = 0.6f;*/
			if (moveFlag) {
				camera->cameraTransform_.translate.x += car_->Speed * move.y;
				camera->cameraTransform_.translate.z += car_->Speed * move.x;
			}
		}
		else if (!(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || !input->PushKey(DIK_LSHIFT))
		{
			//camera->cameraTransform_.rotate = NormalCamera.rotate;
			//camera->cameraTransform_.translate = NormalCamera.translate;
			camera->cameraTransform_.translate.z = car_->GetWorldTransform().z - 25;
			camera->cameraTransform_.translate.y = 6.0f;
			camera->cameraTransform_.rotate.x = NormalCamera.rotate.x;
			if (camera->cameraTransform_.scale.x >= 1.0f) {
				camera->cameraTransform_.scale.x -= 0.05f;
			}
			if (camera->cameraTransform_.scale.y >= 1.0f) {
				camera->cameraTransform_.scale.y -= 0.05f;
			}
			if (camera->cameraTransform_.scale.z <= 1.0f) {
				camera->cameraTransform_.scale.z += 0.02f;
			}
			if (moveFlag) {
				camera->cameraTransform_.translate.x += car_->Speed * move.y;
				camera->cameraTransform_.translate.z += car_->Speed * move.x;
			}
			/*camera->cameraTransform_.scale.x = 1.0f;
			camera->cameraTransform_.scale.y = 1.0f;
			camera->cameraTransform_.scale.z = 1.0f;*/
		}
		break;
	}
	case DriftMode: {
		if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || input->PushKey(DIK_LSHIFT) || (AccelFlag && DriftFlag)) {

			//camera->cameraTransform_.rotate = AccelDriftCamera.rotate;
			//camera->cameraTransform_.translate = AccelDriftCamera.translate;

			camera->cameraTransform_.translate.z = car_->GetWorldTransform().z - 25;
			camera->cameraTransform_.translate.y = 6.0f;
			camera->cameraTransform_.rotate.x = DriftCamera.rotate.x;

			if (camera->cameraTransform_.scale.x <= 2.0f) {
				camera->cameraTransform_.scale.x += 0.05f;
			}
			if (camera->cameraTransform_.scale.y <= 2.0f) {
				camera->cameraTransform_.scale.y += 0.05f;
			}
			if (camera->cameraTransform_.scale.z >= 0.6f) {
				camera->cameraTransform_.scale.z -= 0.02f;
			}
			if (moveFlag) {
				camera->cameraTransform_.translate.x += car_->Speed * move.y;
				camera->cameraTransform_.translate.z += car_->Speed * move.x;
			}
			/*camera->cameraTransform_.scale.x = 2.0f;
			camera->cameraTransform_.scale.y = 2.0f;
		camera->cameraTransform_.scale.z = 0.6f;*/
		}
		else if (!(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || !input->PushKey(DIK_LSHIFT)|| DriftFlag)
		{
			//camera->cameraTransform_.rotate = DriftCamera.rotate;
			//camera->cameraTransform_.translate = DriftCamera.translate;
			camera->cameraTransform_.translate.z = car_->GetWorldTransform().z - 25;
			camera->cameraTransform_.translate.y = 6.0f;
			camera->cameraTransform_.rotate.x = DriftCamera.rotate.x;
			 
			if (camera->cameraTransform_.scale.x >= 1.0f) {
				camera->cameraTransform_.scale.x -= 0.05f;
			}
			if (camera->cameraTransform_.scale.y >= 1.0f) {
				camera->cameraTransform_.scale.y -= 0.05f;
			}
			if (camera->cameraTransform_.scale.z <= 1.0f) {
				camera->cameraTransform_.scale.z += 0.02f;
			}
			if (moveFlag) {
				camera->cameraTransform_.translate.x += car_->DriftSpeed * move.y;
				camera->cameraTransform_.translate.z += car_->DriftSpeed * move.x;
			}
			/*camera->cameraTransform_.scale.x = 1.0f;
			camera->cameraTransform_.scale.y = 1.0f;
			camera->cameraTransform_.scale.z = 1.0f;*/
		}
		break;
	}
	}

}
