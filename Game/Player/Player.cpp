#include "Player.h"
Player::Player() {

}

Player::~Player() {

}

void Player::Init() {
	worldTransform_.Initialize();
	

	model_ = new Model();
	model_->Initialize("Resources/multiMaterial","multiMaterial.obj");
}

void Player::Update() {

}

void Player::Draw(Camera *camera) {
	model_->Draw(worldTransform_, texture_, camera);
}