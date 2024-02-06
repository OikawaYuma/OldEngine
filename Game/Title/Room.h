#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "IScene.h"
#include "TextureManager.h"
#include "Audio.h"
#include "Particle.h"
#include "Sprite.h"
#include "Particle.h"
class Room
{
public:
	Room();
	~Room();
	void Init();
	void Update();
	void Draw(Camera* camera);
	void Release();

	
	Vector3 GetWorldTransform() {
		return worldTransform_.translation_;
	}
	/*int GetDriveMode() {
		return driveMode_;
	}*/
private:
	Model* model_ = nullptr;
	uint32_t texture_ = 1;
	
	Input* input = nullptr;
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	

public:
	WorldTransform worldTransform_;
	float rotate_;
	
};

