#include "Enemy.h"

void Enemy::Init()
{
	floorTex_ = TextureManager::GetInstance()->StoreTexture("Resources/Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.scale_.x = 1.0f;
	worldTransform_.scale_.z = 1.0f;
	worldTransform_.translation_.x =10.0f;
	worldTransform_.translation_.y = 1.0f;
	worldTransform_.translation_.z = 179.0f;

	worldTransform_1.Initialize();
	worldTransform_1.scale_.x = 1.0f;
	worldTransform_1.scale_.z = 1.0f;
	worldTransform_1.translation_.y = 1.0f;
	worldTransform_1.translation_.x = -16.0f;
	worldTransform_1.translation_.z = 611.0f;

	worldTransform_2.Initialize();
	worldTransform_2.scale_.x = 1.0f;
	worldTransform_2.scale_.z = 1.0f;
	worldTransform_2.translation_.x = 21.0f;
	worldTransform_2.translation_.y = 1.0f;
	worldTransform_2.translation_.z = 420.0f;

	worldTransform_3.Initialize();
	worldTransform_3.scale_.x = 1.0f;
	worldTransform_3.scale_.z = 1.0f;
	worldTransform_3.translation_.x = -5.0f;
	worldTransform_3.translation_.y = 1.0f;
	worldTransform_3.translation_.z = 809.0f;

	worldTransform_4.Initialize();
	worldTransform_4.scale_.x = 1.0f;
	worldTransform_4.scale_.z = 1.0f;
	worldTransform_4.translation_.x = 18.0f;
	worldTransform_4.translation_.y = 1.0f;
	worldTransform_4.translation_.z = 133.0f;

	//ModelManager::GetInstance()->LoadModel("Resources/box/", "box.obj");
	object_ = std::make_unique<Object3d>();
	object_->Init();
	object_->SetModel("box.obj");

	object_1 = std::make_unique<Object3d>();
	object_1->Init();
	object_1->SetModel("box.obj");

	object_2 = std::make_unique<Object3d>();
	object_2->Init();
	object_2->SetModel("box.obj");

	object_3 = std::make_unique<Object3d>();
	object_3->Init();
	object_3->SetModel("box.obj");

	object_4 = std::make_unique<Object3d>();
	object_4->Init();
	object_4->SetModel("box.obj");
}

void Enemy::Update()
{
	object_->Update();
	object_->SetWorldTransform(worldTransform_);
	object_1->Update();
	object_1->SetWorldTransform(worldTransform_1);
	object_2->Update();
	object_4->Update();
	object_3->Update();
	object_3->SetWorldTransform(worldTransform_2);
	object_2->SetWorldTransform(worldTransform_3);
	object_4->SetWorldTransform(worldTransform_4);

	worldTransform_.UpdateMatrix();
	worldTransform_1.UpdateMatrix();
	worldTransform_2.UpdateMatrix();
	worldTransform_3.UpdateMatrix();
	worldTransform_4.UpdateMatrix();

}

void Enemy::Draw(Camera* camera)
{
	object_->Draw(floorTex_, camera);
	object_1->Draw(floorTex_, camera);
	object_2->Draw(floorTex_, camera);
	object_3->Draw(floorTex_, camera);
	object_4->Draw(floorTex_, camera);
}
