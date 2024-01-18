#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "IScene.h"
#include "TextureManager.h"
#include "Audio.h"
#include "Particle.h"
#include "Sprite.h"
class Car
{
public:
	Car();
	~Car();
	void Init();
	void Update();
	void Draw(Camera* camera);
	void Release();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 1;
	Input* input = nullptr;
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	Sprite* sprite_ = nullptr;
	Particle* particle = nullptr;
	Camera* camera = nullptr;
	float Speed = 0.0f;
	float NormalSpeed = 0.1f;
	float ShiftSpeed = 0.2f;
};

