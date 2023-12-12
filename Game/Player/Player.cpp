#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	texture_ = TextureManager::StoreTexture("Resources/uvChecker.png");
	texture2_ = TextureManager::StoreTexture("Resources/monsterBall.png");
	audio_ = Audio::GetInstance();
	soundData = audio_->SoundLoadWave("Resources/fanfare.wav");

	model_ = new Model();
	model_->Initialize("Resources/multiMaterial","multiMaterial.obj");
}

void Player::Update() {
	if (input->TriggerKey(DIK_A)) {
		IScene::SetSceneNo(STAGE) ;
	}
	if (input->TriggerKey(DIK_B)) {
		audio_->SoundPlayWave(audio_->GetIXAudio().Get(),soundData);
	}

	if (input->TriggerKey(DIK_N)) {
		audio_->SoundPlayWave(audio_->GetIXAudio().Get(), soundData);
	}
}

void Player::Draw(Camera *camera) {
	model_->Draw(worldTransform_, texture2_, camera);
}