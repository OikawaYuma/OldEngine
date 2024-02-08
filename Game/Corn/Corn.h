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
class Corn
{
public:
	Corn();
	~Corn();
	void Init(Vector3 translation);
	void Update();
	void Draw(Camera* camera,uint32_t texture);
	void Release();
	void SetType(float type) { type_ = type; }
	void SetTranslate(Vector3 translation);
	void SetCornflag(bool cornflag) { cornflag_ = cornflag; }

	Vector3 GetWorldTransform() {
		return worldTransform_.translation_;
	}

	bool GetCornflag()
	{
		return cornflag_;
	}



private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 1;
	Input* input = nullptr;
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	float type_ = 0;
	bool cornflag_ = false;
};

