#include "RailCamera.h"
#include "ImGuiCommon.h"
#include "mathFunction.h"
#include "WinAPI.h"
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
	
	constrolPoint_ = {
		{0,0,0},
		{10,10,0},
		{13,15,0},
		{20,15,15},
		{25,10,10},
		{30,5,0}
	};


	//move.z = 0.0f;
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	camera->viewMatrix_ = Inverse(worldTransform_.matWorld_);

}

void RailCamera::Update(bool flag)
{
	Vector3 move = { 0.0f,0.0f,0.25f };
	// 座標移動（ベクトルの加算）
	//worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// 回転速さ[ラジアン/frame]
	//const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	/*if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}*/
	if (flag) {
		Vector3 demoTranslate = CatmullRomPosition(constrolPoint_, t);

		// 敵弾から自キャラへのベクトル計算

		toDire.x = demoTranslate.x - worldTransform_.matWorld_.m[3][0];
		toDire.y = demoTranslate.y - worldTransform_.matWorld_.m[3][1];
		toDire.z = demoTranslate.z - worldTransform_.matWorld_.m[3][2];

		//float t = 0.01f;

		//// 引数で受け取った速度をメンバ変数に代入
		//velocity_ = SLerp(toPlayer,
		//	{ worldtransform_.matWorld_.m[3][0], worldtransform_.matWorld_.m[3][1],
		//	worldtransform_.matWorld_.m[3][2] }, t);

		//velocity_.x *= 0.7f;
		//velocity_.y *= 0.7f;
		//velocity_.z *= 0.7f;

		// Y軸周り角度（Θy）
		worldTransform_.rotation_.y = std::atan2(toDire.x, toDire.z);
		float velocityXZ = sqrt((toDire.x * toDire.x) + (toDire.z * toDire.z));

		worldTransform_.rotation_.x = std::atan2(-toDire.y, velocityXZ);


		worldTransform_.translation_ = CatmullRomPosition(constrolPoint_, t);
		t += 0.001f;
	}
	//UpdateMatrix();
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	//camera->Update();
	// カメラオブジェクトのワールド行列からビュー行列を計算する
	camera->viewMatrix_ = Inverse(worldTransform_.matWorld_);

	//cameraMatrix_ = MakeAffineMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	//iewMatrix_ = Inverse(cameraMatrix_);
	camera->projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(WinAPI::kClientWidth_) / float(WinAPI::kClientHeight_), 0.1f, 100.0f);
	//worldViewProjectionMatrix_ = Multiply(worldmatrix_, Multiply(viewMatrix_, projectionMatrix_));


}
