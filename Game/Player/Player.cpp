#include "Player.h"
#include "ImGuiCommon.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "mathFunction.h"
Player::Player() {

}

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Init() {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 40;
	worldTransform_.UpdateMatrix();
	texture_ = TextureManager::StoreTexture("Resources/white.png");
	texture2_ = TextureManager::StoreTexture("Resources/monsterBall.png");
	texture3_ = TextureManager::StoreTexture("Resources/Reticle.png");
	soundData = Audio::SoundLoadWave("Resources/fanfare.wav");
	soundData2 = Audio::SoundLoadWave("Resources/fanfare.wav");
	// 3Dレティクルのワールドトラベル初期化
	worldTransform3DReticle_.Initialize();
	material.color = color;
	material.enableLighting = true;
	material.shininess = 5.0f;
	dir_.direction = { 0.0f,-1.0f,0.0f };
	model_ = new Model();
	model_->Initialize("Resources/ball", "ball.obj", material);
	particle = new Particle();
	particle->Initialize({ 1.0f, 1.0f, 1.0f, 1.0f });
	sprite_ = new Sprite;
	sprite_->Initialize(color);

	sprite2DReticle_ = new Sprite();
	sprite2DReticle_->Initialize({ color });
	sprite2DReticle_->SetSize({ 100, 100});
	sprite2DReticle_->SetPosition({ 500,500 });
	sprite2DReticle_->SetAnchorPoint({ 0.5f,0.5f });
	sprite2DReticle_->Update();
	// 衝突属性を設定
	SetCollisonAttribute(0);

	// 衝突対象を自分の属性以外に設定
	SetCollisionMask(1);
}

void Player::Update(Camera* camera) {

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	float theta = (rotate_ / 2.0f) * (float)M_PI;
	worldTransform_.rotation_.y = theta;
	if (input->PushKey(DIK_A)) {
		worldTransform_.translation_.x-= 0.5f;
	}
	if (input->PushKey(DIK_D)) {
		worldTransform_.translation_.x+= 0.5f;
	}
	if (input->PushKey(DIK_W)) {
		worldTransform_.translation_.y+= 0.5f;
	}

	if (input->PushKey(DIK_S)) {
		worldTransform_.translation_.y-= 0.5f;
	}
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	{
		// ゲームパッドの状態を得る変数（XINPUT）
		XINPUT_STATE joyState;

		// ゲームパッド状態取得
		if (Input::GetInstance()->GetJoystickState(joyState)) {
			worldTransform_.translation_.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
			worldTransform_.translation_.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
		}
	}

	/*if (input->PushKey(DIK_RIGHTARROW)) {
		rotate_ += 0.01f;
	}*/
	
		/*rotate_ -= 0.01f;
		if (red_ <=1.0f) {
			red_ += 0.01f;
			if (red_ > 1.0f) {
				red_ = 0.1f;
			}
		}
		if (blue_ <= 1.0f) {
			blue_ += 0.01f;
			if (blue_ > 1.0f) {
				blue_ = 0.4f;
			}
		}
		if (green_ <= 1.0f) {
			green_ += 0.01f;
			if (green_ > 1.0f) {
				green_ = 0.6f;
			}
		}*/





	// スプライトの現在座標を取得
	Vector2 spritePosition = sprite2DReticle_->GetPosition();
	if (Input::GetInstance()->PushKey(DIK_RIGHTARROW)) {
		spritePosition.x+=5;
	}
	if (Input::GetInstance()->PushKey(DIK_LEFTARROW)) {
		spritePosition.x-=5;
	}
	if (Input::GetInstance()->PushKey(DIK_UPARROW)) {
		spritePosition.y-=5;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWNARROW)) {
		spritePosition.y+=5;
	}
	sprite2DReticle_->SetPosition(spritePosition);
	{
		// スプライトの現在座標を取得
		Vector2 spritePosition = sprite2DReticle_->GetPosition();

		XINPUT_STATE joyState1;

		// ジョイスティック状態取得
		if (Input::GetInstance()->GetJoystickState(joyState1)) {
			spritePosition.x += (float)joyState1.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
			spritePosition.y -= (float)joyState1.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
			// スプライトの座標変更を繁栄
			sprite2DReticle_->SetPosition(spritePosition);
		}

	}
	sprite2DReticle_->Update();
	// ビューポート
	Matrix4x4 matViewport =
		MakeViewportMatrix(0, 0, WinAPI::kClientWidth_, WinAPI::kClientHeight_, 0, 1);

	/*--------合成行列の逆行列--------------*/
		// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV =
		Multiply(Multiply(camera->viewMatrix_, camera->projectionMatrix_), matViewport);
	// 合成行列の逆行列を計算する

	Matrix4x4 matInverseVPV = Inverse(matVPV);

	/*--------2点のワールド行列--------------*/
	// スクリーン座標
	Vector3 posNear = Vector3(static_cast<float>(spritePosition.x), (float)spritePosition.y, 0);
	Vector3 posFar = Vector3(static_cast<float>(spritePosition.x), float(spritePosition.y), 1);
	// スクリーン座標系からワールド座標系へ
	posNear = Transform1(posNear, matInverseVPV);
	posFar = Transform1(posFar, matInverseVPV);

	/*---------3Dレティクルの座標系さん-------*/
	// スティックレイの方向
	Vector3 spriteDierection;
	spriteDierection.x = posFar.x - posNear.x;
	spriteDierection.y = posFar.y - posNear.y;
	spriteDierection.z = posFar.z - posNear.z;
	spriteDierection = Normalize(spriteDierection);
	// カメラから照準オブジェクトの距離
	const float kDistanceTextObject = 100.0f;
	worldTransform3DReticle_.translation_.x = spriteDierection.x * kDistanceTextObject;
	worldTransform3DReticle_.translation_.y = spriteDierection.y * kDistanceTextObject;
	worldTransform3DReticle_.translation_.z = spriteDierection.z * kDistanceTextObject;

	worldTransform3DReticle_.UpdateMatrix();



	//XINPUT_STATE joyState1;

	//// ジョイスティック状態取得
	//if (Input::GetInstance()->GetJoystickState(0, joyState1)) {
	//	spritePosition.x += (float)joyState1.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
	//	spritePosition.y -= (float)joyState1.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
	//	// スプライトの座標変更を繁栄
	//	sprite2DReticle_->SetPosition(spritePosition);
	//}

	// キャラクター攻撃処理
	Attack();
	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	color = { red_,green_,blue_,1.0f };
	ImGui::Begin("Color");
	ImGui::DragFloat4("s",&worldTransform_.scale_.x,0.01f);
	ImGui::DragFloat4("r", &worldTransform_.rotation_.x,  0.01f);
	ImGui::DragFloat4("t", &worldTransform_.translation_.x,  0.01f);
	ImGui::DragFloat4("color", &material.color.x, 0.01f);
	ImGui::DragFloat("MaterialShininess", &material.shininess, 0.01f);
	ImGui::DragFloat3("LightDirection", &dir_.direction.x, 0.01f);
	ImGui::Text("3DreticleightDirection   %f,%f,%f", worldTransform3DReticle_.translation_.x, worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::Text("Wold   %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);

	ImGui::End();
	dir_.direction = Normalize(dir_.direction);
	//Audio::SoundLoopWave(Audio::GetIXAudio().Get(), soundData);
	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera *camera) {

	model_->Draw(worldTransform_, texture_, camera,material,dir_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
	//sprite_->Draw(texture_,color);
	particle->Draw(texture_, color, camera);
	
}

void Player::Release()
{
	Audio::SoundUnload(soundData2);
}

void Player::Attack()
{
	if (input->TriggerKey(DIK_SPACE)) {
		
		// 自キャラの座標をコピー
		Vector3 position = worldTransform_.translation_;

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 自機から照準オブジェクトへのベクトル
		velocity.x = GetReticleWorldPosition().x - GetWorldPosition().x;
		velocity.y = GetReticleWorldPosition().y - GetWorldPosition().y;
		velocity.z = GetReticleWorldPosition().z - GetWorldPosition().z;

		velocity = Normalize(velocity);
		velocity.x *= kBulletSpeed;
		velocity.y *= kBulletSpeed;
		velocity.z *= kBulletSpeed;

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		//velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Init(GetWorldPosition(), velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);


	}
	{
		// ゲームパッドを押したときの処理
		XINPUT_STATE joyState;

		// ゲームパッド未接続なら何もせず抜ける
		if (!Input::GetInstance()->GetJoystickState(joyState)) {
			return;
		}

		// Rトリガーを押していたら
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			// 弾があれば破棄する
			/*if (bullet_) {
				delete bullet_;
				bullet_ = nullptr;
			}*/
			// 弾の速度
			const float kBulletSpeed = 0.5f;
			Vector3 velocity(0, 0, 0);

			// 自機から照準オブジェクトへのベクトル
			velocity.x = GetReticleWorldPosition().x - GetWorldPosition().x;
			velocity.y = GetReticleWorldPosition().y - GetWorldPosition().y;
			velocity.z = GetReticleWorldPosition().z - GetWorldPosition().z;

			velocity = Normalize(velocity);
			velocity.x *= kBulletSpeed;
			velocity.y *= kBulletSpeed;
			velocity.z *= kBulletSpeed;

			// 速度ベクトルを自機の向きに合わせて回転させる
			velocity = TransformNormal(velocity, worldTransform_.matWorld_);

			// 弾を生成し、初期化
			PlayerBullet* newBullet = new PlayerBullet();
			newBullet->Init(GetWorldPosition(), velocity);

			// 弾を登録する
			bullets_.push_back(newBullet);
		}
	}
}

void Player::OnCollision()
{
}

Vector3 Player::GetWorldPosition() const
{
	// ワールド行列座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::SetParent(const WorldTransform* parent)
{
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
	worldTransform3DReticle_.parent_ = parent;
}

void Player::DrawUI()
{
	// スプライト生成
	sprite2DReticle_->Draw(texture3_, {1.0f,1.0f,1.0f,1.0f});
}

Vector3 Player::GetWorldPosition() {
	// ワールド行列座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::GetReticleWorldPosition() {
	// ワールド行列座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	return worldPos;
}