#include "Player.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Input.h"
#include "Model.h"

#include "ImGuiCommon.h"

void Player::Init()
{
	floorTex_ = TextureManager::GetInstance()->StoreTexture("Resources/white.png");
	worldTransform_.Initialize();
	worldTransform_.translation_.y = 1.0f;
	
	ModelManager::GetInstance()->LoadModel("Resources/box/", "box.obj");
	object_ = std::make_unique<Object3d>();
	object_->Init();
	object_->SetModel("box.obj");
	
	
	


}

void Player::Update()
{

	Vector3 camerarotate_ = camera_->GetRotate();
	Vector3 preCameraToPlayerDistance = cameraToPlayerDistance_;
	float cameraFarY = 50.0f;
	ImGui::Begin("Player & camera");

	ImGui::DragFloat3("playerScale", &worldTransform_.scale_.x);

	ImGui::DragFloat3("cameraRotate", &camerarotate_.x, 0.01f);
	ImGui::DragFloat3("cameraTranslate", &preCameraToPlayerDistance.x, 0.01f);
	ImGui::DragFloat("cameraForY", &cameraFarY, 2.5f);
	ImGui::End();
	camera_->SetRotate(camerarotate_);
	camera_->SetFarClip(cameraFarY);
	cameraToPlayerDistance_ = preCameraToPlayerDistance;

	object_->Update();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && !isJump_) {
		isJump_ = true;
		accel_ = 1;
	}

	if (Input::GetInstance()->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= 0.5f;
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		worldTransform_.translation_.x += 0.5f;
	}

	if (Input::GetInstance()->PushKey(DIK_P)) {
		worldTransform_.scale_ = Add(worldTransform_.scale_, {0.05f,0.05f,0.05f});
		worldTransform_.translation_.y += 0.05f;
	}
	if (Input::GetInstance()->PushKey(DIK_O)) {
		worldTransform_.scale_ = Subtract(worldTransform_.scale_, { 0.05f,0.05f,0.05f });
		worldTransform_.translation_.y -= 0.05f;
	}



	if (isJump_) {
		worldTransform_.translation_.y += accel_;
		accel_ -= 0.04f;
	}
	if (worldTransform_.translation_.y <= worldTransform_.scale_.y && isJump_) {
		worldTransform_.translation_.y = worldTransform_.scale_.y += 0.1f;
		accel_ = 0.0f;
		isJump_ = false;
	}
	//worldTransform_.translation_.z += 1.0f;
	worldTransform_.UpdateMatrix();
	camera_->SetTranslate({ 
		worldTransform_.translation_.x + cameraToPlayerDistance_.x,
		worldTransform_.translation_.y + cameraToPlayerDistance_.y, 
		worldTransform_.translation_.z + cameraToPlayerDistance_.z });
	object_->SetWorldTransform(worldTransform_);
}

void Player::Draw(Camera* camera)
{
	object_->Draw(floorTex_,camera);
}

