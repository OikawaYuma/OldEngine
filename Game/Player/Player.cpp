#include "Player.h"
#include "ImGuiCommon.h"
Player::Player() {

}

Player::~Player() {

}

void Player::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	texture_ = TextureManager::StoreTexture("Resources/circle.png");
	texture2_ = TextureManager::StoreTexture("Resources/monsterBall.png");
	soundData = Audio::SoundLoadWave("Resources/fanfare.wav");
	soundData2 = Audio::SoundLoadWave("Resources/fanfare.wav");
	model_ = new Model();
	model_->Initialize("Resources/car","car.obj",color);
	particle = new Particle();
	particle->Initialize({ 1.0f, 1.0f, 1.0f, 1.0f });
	sprite_ = new Sprite;
	sprite_->Initialize(color);
}

void Player::Update() {
	if (input->TriggerKey(DIK_A)) {
		IScene::SetSceneNo(STAGE) ;
	}
	if (input->TriggerKey(DIK_B)) {
		Audio::SoundPlayWave(Audio::GetIXAudio().Get(),soundData2,true);
	}
	if (input->TriggerKey(DIK_N)) {
		Audio::SoundPlayWave(Audio::GetIXAudio().Get(), soundData2,true);
	}

	if (input->TriggerKey(DIK_O)) {
		Audio::SoundStopWave(Audio::GetIXAudio().Get(), soundData2);
	}

	if (input->PushKey(DIK_J)) {
		worldTransform_.translation_.y--;
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
	//sprite_->Draw(texture_,color);
	particle->Draw(texture_, color, camera);
}

void Player::Release()
{
	Audio::SoundUnload(soundData2);
}
