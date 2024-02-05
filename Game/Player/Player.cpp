#include "Player.h"
#include "ImGuiCommon.h"
Player::Player() {

}

Player::~Player() {

}

void Player::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	texture_ = TextureManager::StoreTexture("Resources/monsterBall.png");
	texture2_ = TextureManager::StoreTexture("Resources/monsterBall.png");
	soundData = Audio::SoundLoadWave("Resources/fanfare.wav");
	soundData2 = Audio::SoundLoadWave("Resources/fanfare.wav");

	material.color = color;
	material.enableLighting = true;
	material.shininess = 5.0f;
	dir_.direction = { 0.0f,-1.0f,0.0f };
	model_ = new Model();
	model_->Initialize("Resources/ball","ball.obj",material);
	particle = new Particle();
	particle->Initialize({ 1.0f, 1.0f, 1.0f, 1.0f });
	sprite_ = new Sprite;
	sprite_->Initialize(color);
}

void Player::Update() {
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

	if (input->PushKey(DIK_J)) {
		worldTransform_.translation_.y--;
	}
	

	ImGui::Begin("task2");
	/*ImGui::DragFloat4("s",&worldTransform_.scale_.x,0.01f);
	ImGui::DragFloat4("r", &worldTransform_.rotation_.x,  0.01f);
	ImGui::DragFloat4("t", &worldTransform_.translation_.x,  0.01f);
	ImGui::DragFloat4("color", &material.color.x, 0.01f);*/
	ImGui::DragFloat("MaterialShininess", &material.shininess, 0.01f);
	ImGui::DragFloat3("LightDirection", &dir_.direction.x, 0.01f);
	ImGui::End();
	dir_.direction = Normalize(dir_.direction);
	//Audio::SoundLoopWave(Audio::GetIXAudio().Get(), soundData);
	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera *camera) {
	model_->Draw(worldTransform_, texture2_, camera,material,dir_);
	//sprite_->Draw(texture_,color);
	particle->Draw(texture_, color, camera);
}

void Player::Release()
{
	Audio::SoundUnload(soundData2);
}
