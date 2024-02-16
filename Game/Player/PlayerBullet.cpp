#include "PlayerBullet.h"

//#include "GameScene.h"
void PlayerBullet::Init(const Vector3& pos,const Vector3& velocity)
{
	// NULLポインタチェック
	//assert(model);
	material.color = color;
	material.enableLighting = true;
	material.shininess = 5.0f;
	dir_.direction = { 0.0f,-1.0f,0.0f };
	model_ = new Model();
	model_->Initialize("Resources/box", "box.obj", material);
	// テクスチャ読み込み
	//textureHandle_ = TextureManager::StoreTexture("Resources/uvChecker.png");

	worldtransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldtransform_.translation_ = pos;

	velocity_ = velocity;
	// 衝突属性を設定
	SetCollisonAttribute(0);

	// 衝突対象を自分の属性以外に設定
	SetCollisionMask(1);
}

void PlayerBullet::Update()
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	worldtransform_.translation_ = Add(worldtransform_.translation_, velocity_);
	worldtransform_.UpdateMatrix();

}

void PlayerBullet::Draw(Camera* camera)
{
	model_->Draw(worldtransform_, 1, camera, material,dir_);
}

void PlayerBullet::OnCollision()
{
	//GameScene::SetChangeScene();
}

Vector3 PlayerBullet::GetWorldPosition() const
{
	// ワールド行列座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}
