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
#include "PlayerBullet.h"
#include "Material.h"
#include "DirectionLight.h"
#include "Collider.h"
class Player : public Collider
{
public:
	Player();
	~Player();
	void Init();
	void Update(Camera* camera);
	void Draw(Camera *camera);
	void Release();

	void Attack(const WorldTransform* parent);
	int GetRadius() { return radius_; }
	// 弾リストを取得
	const std::list<PlayerBullet*>& Getbullet() const { return bullets_; }
	// 衝突を検出したらコールバック関数
	void OnCollision()override;
	Vector3 GetWorldPosition()const override;
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// UI描画
	/// </summary>	
	void DrawUI();
	Vector3 GetWorldPosition();
	Vector3 GetReticleWorldPosition();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Model* model3DR_ = nullptr;
	uint32_t texture_ =1;
	uint32_t texture2_ = 1;
	uint32_t texture3_ = 1;
	Input* input =nullptr;
	uint32_t soundData;
	uint32_t soundData2;
	Vector4 color = {1.0f,1.0f,1.0f,1.0f};
	Sprite* sprite_ = nullptr;
	DirectionalLight dir_;
	Material material;
	Particle* particle = nullptr;
	float rotate_;
	float red_ = 1.0f;
	float green_ = 1.0f;
	float blue_ = 1.0f;
	int radius_ = 1;
	// 弾
	std::list<PlayerBullet*> bullets_ ;


	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;

	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;
};

