#include "Player.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Input.h"
#include "Model.h"

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

	if (isJump_) {
		worldTransform_.translation_.y += accel_;
		accel_ -= 0.04f;
	}
	if (worldTransform_.translation_.y <= 1.0f && isJump_) {
		accel_ = 0.0f;
		isJump_ = false;
	}
	worldTransform_.translation_.z += 1.0f;
	worldTransform_.UpdateMatrix();
	camera_->SetTranslate({ worldTransform_.translation_.x,worldTransform_.translation_.y+ 10, worldTransform_.translation_.z - 50 });
	object_->SetWorldTransform(worldTransform_);
}

void Player::Draw(Camera* camera)
{
	object_->Draw(floorTex_,camera);
}

