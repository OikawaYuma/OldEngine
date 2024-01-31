#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Particle.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "CollisionManager.h"

class GameScene :public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;
	static void SetChangeScene();
	private:
	Input* input = nullptr;
	int sceneTime = 0;
	Camera* camera = nullptr;
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;
	Sprite* sprite_ = nullptr;
	float fadeColor_ = 1.0f;
	uint32_t textureHandle_;
	bool startFlag_ = false;
	static bool sceneChange;
	CollisionManager* collisionManager_ = nullptr;
};

