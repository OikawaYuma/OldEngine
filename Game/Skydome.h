#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "Material.h"
#include "DirectionLight.h"
#include "Camera.h"

class Skydome
{
public:
	void Init();
	void Update();
	void Draw(Camera* camera);
	void Release();
private:
	uint32_t textureHandle_;
	WorldTransform worldTransform;
	DirectionalLight dir_;
	Material material_;
	Model* model_ = nullptr;
};
