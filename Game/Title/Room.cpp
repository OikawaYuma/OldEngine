#include "Room.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::Init()
{
	model_ = new Model();
	model_->Initialize("Resources/room", "room.obj", { 1.0f,1.0f,1.0f,1.0f }, true);
	texture_ = TextureManager::StoreTexture("Resourcess/room/room.png");
	worldTransform_.Initialize();
	worldTransform_.UpdateMatrix();
}

void Room::Update()
{
}

void Room::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, texture_, camera, {1.0f,1.0f,1.0f,1.0f});
}

void Room::Release()
{
}
