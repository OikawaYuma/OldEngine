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
#include "list"
#include "IEnemy.h"
#include "EnemyBullet.h"

#include "TimedCall.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init();
	void Update();
	void Draw(Camera* camera);
	void Release();

	void FazeInit();
	void Fire();
	void Move();
	Vector3 GetVelo()
	{
		return velocity_;
	}

	Vector3 GetTranslation() { return worldTransform_.translation_; }
	//setter
	void SetVelo(Vector3 velocity);
	void SetFireTimer(int fireTimer);
	// state
	void ChangeState(IEnemy* newState);
	void FireCount();
	int GetFireTimer() { return FireTimer; };

	const static int kFireInterval = 60;

	void FireLoop();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 1;
	uint32_t texture2_ = 1;
	Input* input = nullptr;
	uint32_t soundData;
	uint32_t soundData2;
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	Sprite* sprite_ = nullptr;
	Particle* particle = nullptr;
	float rotate_;
	IEnemy* state;
	Vector3 velocity_;

private:
	int32_t FireTimer = 0;

	// 弾
	std::list<EnemyBullet*> bullets_;
	std::function<void(void)> fireLoop;
	// 時限発動のリスト
	std::list<TimedCall*> timedCalls_;

};

