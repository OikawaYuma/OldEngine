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

