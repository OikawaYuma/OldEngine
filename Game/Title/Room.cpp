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
	model_ = new Model();
	model_->Initialize("Resources/room", "room.obj", color,false);
	modelFront_ = new Model();
	modelFront_->Initialize("Resources/room", "roomFront.obj", color,false);
	shutter_ = new Model();
	shutter_->Initialize("Resources/room", "shutter.obj", color,true);
	texture_ = TextureManager::StoreTexture("Resources/room/room.png");
	texture2_ = TextureManager::StoreTexture("Resources/room/shutter.png");
	texture3_ = TextureManager::StoreTexture("Resources/room/roomFront.png");
	
}

void Room::Update()
{
}

void Room::Draw(Camera* camera)
{
	shutter_->Draw(worldTransform_, texture2_, camera, color);
	model_->Draw(worldTransform_, texture_, camera, color);
	modelFront_->Draw(worldTransform_, texture3_, camera, color);
}

void Room::Release()
{
}
