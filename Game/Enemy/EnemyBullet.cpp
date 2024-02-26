#include "EnemyBullet.h"
#include "Player.h"

void EnemyBullet::Init(const Vector3& pos, const Vector3& velocity)
{
	// NULLポインタチェック
	//assert(model);
	color = { 1.0f,1.0f,1.0f,1.0f };
	model_ = new Model();
	model_->Initialize("Resources/box", "box.obj", material);
	// テクスチャ読み込み
	//textureHandle_ = TextureManager::StoreTexture("Resources/uvChecker.png");

	worldtransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldtransform_.translation_ = pos;
	worldtransform_.UpdateMatrix();
	velocity_ = velocity;
	SetCollisonAttribute(1);
	SetCollisionMask(0);
	material.color = color;
	material.enableLighting = true;
	material.shininess = 5.0f;
	dir_.direction = { 0.0f,-1.0f,0.0f };
	
}

void EnemyBullet::Update()
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// 敵弾から自キャラへのベクトル計算
	Vector3 toPlayer;
	toPlayer.x = player_->GetWorldPosition().x - worldtransform_.matWorld_.m[3][0];
	toPlayer.y = player_->GetWorldPosition().y - worldtransform_.matWorld_.m[3][1];
	toPlayer.z = player_->GetWorldPosition().z - worldtransform_.matWorld_.m[3][2];

	float t = 0.01f;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = SLerp(toPlayer,
		{ worldtransform_.matWorld_.m[3][0], worldtransform_.matWorld_.m[3][1],
		worldtransform_.matWorld_.m[3][2] }, t);

	velocity_.x *= 0.7f;
	velocity_.y *= 0.7f;
	velocity_.z *= 0.7f;

	// Y軸周り角度（Θy）
	worldtransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	float velocityXZ = sqrt((velocity_.x * velocity_.x) + (velocity_.z * velocity_.z));

	worldtransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ);



	worldtransform_.translation_ = Add(worldtransform_.translation_, velocity_);
	worldtransform_.UpdateMatrix();

}

void EnemyBullet::Draw(Camera* camera)
{
	model_->Draw(worldtransform_, 1, camera, material,dir_);
}

void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 EnemyBullet::GetWorldPosition() const
{
	// ワールド行列座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}

