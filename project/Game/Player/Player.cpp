#include "Player.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Model.h"

void Player::Init()
{
	platerTex_ = TextureManager::GetInstance()->StoreTexture("Resources/uvChecker.png");
	worldTransform_.Initialize();
	ModelManager::GetInstance()->LoadModel("Resources/box/", "box.obj");
	object_ = std::make_unique<Object3d>();
	object_->Init();
	object_->SetModel("box.obj");
	
	


}

void Player::Update()
{
	object_->Update();

	worldTransform_.translation_.z += 1.0f;
	worldTransform_.UpdateMatrix();
	object_->SetWorldTransform(worldTransform_);
}

void Player::Draw(Camera* camera)
{
	object_->Draw(platerTex_,camera);
}

