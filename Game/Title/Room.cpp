#include "Room.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::Init()
{
	/*model_ = new Model();
	model_->Initialize("Resources/room", "room.obj", { 1.0f,1.0f,1.0f,1.0f }, true);*/
	//texture_ = TextureManager::StoreTexture("Resourcess/room/room.png");
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 10;
	worldTransform_.UpdateMatrix();
	worldTransform2_.Initialize();
	worldTransform2_.translation_.z = 10;
	worldTransform2_.UpdateMatrix();
	model_ = new Model();
	model_->Initialize("Resources/room", "room.obj", color,false);
	shutter_ = new Model();
	shutter_->Initialize("Resources/room", "shutter.obj", color,false);
	texture_ = TextureManager::StoreTexture("Resources/room/room.png");
	texture2_ = TextureManager::StoreTexture("Resources/room/shutter.png");
	texture3_ = TextureManager::StoreTexture("Resources/room/roomFront.png");
	
}

void Room::Update(bool Flag)
{
	if (Flag) {
		time++;
	}
	if (time >= 150) {
		worldTransform2_.translation_.y += 0.05f;
		worldTransform2_.UpdateMatrix();
	}
}

void Room::Draw(Camera* camera)
{
	shutter_->Draw(worldTransform2_, texture2_, camera, color);
	model_->Draw(worldTransform_, texture_, camera, color);
}

void Room::Release()
{
}
