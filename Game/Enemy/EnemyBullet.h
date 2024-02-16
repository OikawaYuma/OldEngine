#pragma once
#include "Model.h"
#include "Camera.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include "Collider.h"
#include "Material.h"
class Player;
class EnemyBullet : public Collider 
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
	// 衝突を検出したらコールバック関数
	void OnCollision()override;
	Vector3 GetWorldPosition() const override;

	void SetPlayer(Player* player) { player_ = player; };
private:
	WorldTransform worldtransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	Material material;
	Vector3 velocity_;
	DirectionalLight dir_;
	static const int32_t kLifeTime = 60 * 5;
	Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
	Player* player_ = nullptr;
};

