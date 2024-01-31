#include "EnemyBullet.h"

void EnemyBullet::Init(const Vector3& pos, const Vector3& velocity)
{
	// NULLポインタチェック
	//assert(model);

	model_ = new Model();
	model_->Initialize("Resources/box", "box.obj", color);
	// テクスチャ読み込み
	//textureHandle_ = TextureManager::StoreTexture("Resources/uvChecker.png");

	worldtransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldtransform_.translation_ = pos;

	velocity_ = velocity;
	SetCollisonAttribute(1);

	SetCollisionMask(0);
}

void EnemyBullet::Update()
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldtransform_.translation_ = Add(worldtransform_.translation_, velocity_);
	worldtransform_.UpdateMatrix();

}

void EnemyBullet::Draw(Camera* camera)
{
	model_->Draw(worldtransform_, 1, camera, { 1.0f,1.0f,1.0f,1.0f });
}

void EnemyBullet::OnCollision()
{
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

