#include "PlayerBullet.h"

void PlayerBullet::Init(Model* model, const Vector3& pos)
{
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::StoreTexture("Resources/uvChecker.png");

	worldtransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldtransform_.translation_ = pos;

}

void PlayerBullet::Update()
{
	worldtransform_.UpdateMatrix();
}

void PlayerBullet::Draw(Camera* camera)
{
	model_->Draw(worldtransform_, 1, camera, {1.0f,1.0f,1.0f,1.0f});
}
