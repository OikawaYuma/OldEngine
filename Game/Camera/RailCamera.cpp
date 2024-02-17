#include "RailCamera.h"
#include "ImGuiCommon.h"
#include "mathFunction.h"
void RailCamera::Init(const Vector3& pos, const Vector3& rot)
{
	camera = new Camera();
	camera->Initialize();
	// 引数でワールド座標を受け取ってワールドトランスフォームに設定
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;
	worldTransform_.translation_.z = pos.z - 15;
	// 引数で回転角[ラジアンを受け取ってワールドトランスフォームに設定
	worldTransform_.rotation_ = rot;
	// ビュープロジェクションの初期化
	//viewProjection_.farZ = 10000.0f;
	
	//move.z = 0.0f;
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

}

void RailCamera::Update()
{
	Vector3 move = { 0.0f,0.0f,0.25f };
	// 座標移動（ベクトルの加算）
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	/*if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}*/

	//.UpdateMatrix();
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	// カメラオブジェクトのワールド行列からビュー行列を計算する
	camera->viewMatrix_ = Inverse(worldTransform_.matWorld_);


}
