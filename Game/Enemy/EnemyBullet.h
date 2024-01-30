#pragma once
#include "Model.h"
#include "Camera.h"
#include "Vector3.h"
#include "WorldTransform.h"
class EnemyBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init(const Vector3& pos, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	void Draw(Camera* camera);

	bool IsDead()const { return isDead_; }

private:
	WorldTransform worldtransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	Vector3 velocity_;

	static const int32_t kLifeTime = 60 * 5;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};

