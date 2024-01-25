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
#include "Particle.h"

enum DriveMode {
	Normal,
	Drift
};

//enum SpeedMode {
//	Normal,
//	Accel
//};

class Car
{
public:
	
	Car();
	~Car();
	void Init();
	void Update();
	void Draw(Camera* camera);
	void Release();
	Vector3 GetWorldTransform() {
		return worldTransform_.translation_;
	}
private:
	Model* model_ = nullptr;
	uint32_t texture_ = 1;
	uint32_t texture2_ = 2;
	Input* input = nullptr;
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	Sprite* sprite_ = nullptr;
	Particle* particle = nullptr;
	Camera* camera = nullptr;

public:
	WorldTransform worldTransform_;
	float rotate_;
	float Speed = 0.0f;
	float NormalSpeed = 1.5f;
	float ShiftSpeed = 2.0f;
	float DriftSpeed = 1.2f;
	bool moveFlag_ = false;
	Vector2 move;
	//Particle* particle = nullptr;
	//std::list<Particle::ParticlePro> particles_;

};

