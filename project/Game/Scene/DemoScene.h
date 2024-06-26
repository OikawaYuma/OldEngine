#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Particle.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "PostProcess.h"

class DemoScene : public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void PostDraw()override;
	void Release()override;
	int GameClose()override;

private:
	int sceneTime = 0;
	Camera* camera = nullptr;
	Input* input = nullptr;
	Sprite* demoSprite = nullptr;

	//変数
	uint32_t textureHandle;
	uint32_t textureHandle2;

	Material material;

	WorldTransform worldTransform;
	WorldTransform worldTransform2;
	Emitter demoEmitter_;
	RandRangePro demoRandPro;
	
	PostProcess* postProcess_ = nullptr;
	std::vector<Object3d*> object3d_;


	float rotateSize_ = 1.057f;
};

