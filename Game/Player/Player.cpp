#include "Player.h"
#include "ImGuiCommon.h"
#define _USE_MATH_DEFINES
#include<math.h>
Player::Player() {

}

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	texture_ = TextureManager::StoreTexture("Resources/circle.png");
	texture2_ = TextureManager::StoreTexture("Resources/monsterBall.png");
	soundData = Audio::SoundLoadWave("Resources/fanfare.wav");
	soundData2 = Audio::SoundLoadWave("Resources/fanfare.wav");
	model_ = new Model();
	model_->Initialize("Resources/box","box.obj",color);
	particle = new Particle();
	particle->Initialize({ 1.0f, 1.0f, 1.0f, 1.0f });
	sprite_ = new Sprite;
	sprite_->Initialize(color);
}

void Player::Update() {

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	float theta = (rotate_ / 2.0f) * (float)M_PI;
	worldTransform_.rotation_.y = theta;
	if (input->PushKey(DIK_A)) {
		worldTransform_.translation_.x-= 0.5f;
	}
	if (input->PushKey(DIK_D)) {
		worldTransform_.translation_.x+= 0.5f;
	}
	if (input->PushKey(DIK_W)) {
		worldTransform_.translation_.y+= 0.5f;
	}

	if (input->PushKey(DIK_S)) {
		worldTransform_.translation_.y-= 0.5f;
	}

	if (input->PushKey(DIK_RIGHTARROW)) {
		rotate_ += 0.01f;
	}
	if (input->PushKey(DIK_LEFTARROW)) {
		rotate_ -= 0.01f;
	}
	
	// キャラクター攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	ImGui::Begin("Color");
	ImGui::DragFloat4("s",&worldTransform_.scale_.x,0.01f);
	ImGui::DragFloat4("r", &worldTransform_.rotation_.x,  0.01f);
	ImGui::DragFloat4("t", &worldTransform_.translation_.x,  0.01f);
	ImGui::End();
	//Audio::SoundLoopWave(Audio::GetIXAudio().Get(), soundData);
	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera *camera) {
	model_->Draw(worldTransform_, texture_, camera,color);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
	//sprite_->Draw(texture_,color);
	particle->Draw(texture_, color, camera);
	
}

void Player::Release()
{
	Audio::SoundUnload(soundData2);
}

void Player::Attack()
{
	if (input->TriggerKey(DIK_SPACE)) {
		
		// 自キャラの座標をコピー
		Vector3 position = worldTransform_.translation_;

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Init(worldTransform_.translation_,velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);


	}
}
