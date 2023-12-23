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
	soundData = Audio::SoundLoadWave("Resources/fanfare.wav");
	soundData2 = Audio::SoundLoadWave("Resources/fanfare.wav");
	model_ = new Model();
	model_->Initialize("Resources/multiMaterial","multiMaterial.obj");

	sprite_ = new Sprite;
	sprite_->Initialize();
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
	//Audio::SoundLoopWave(Audio::GetIXAudio().Get(), soundData);
}

void Player::Draw(Camera *camera) {
	model_->Draw(worldTransform_, texture2_, camera);
	sprite_->Draw(texture_);
}

void Player::Release()
{
	Audio::SoundUnload(soundData2);
}
