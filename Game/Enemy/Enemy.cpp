#include "Enemy.h"
#include "ImGuiCommon.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"EnemyApproach.h"
#include "GameScene.h"
#include "Player.h"
Enemy::Enemy() {

}

Enemy::~Enemy() {
	/*for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}*/
}

void Enemy::Init(GameScene * gamescene) {
	input = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 40;
	worldTransform_.UpdateMatrix();
	texture_ = TextureManager::StoreTexture("Resources/circle.png");
	texture2_ = TextureManager::StoreTexture("Resources/monsterBall.png");
	soundData = Audio::SoundLoadWave("Resources/fanfare.wav");
	soundData2 = Audio::SoundLoadWave("Resources/fanfare.wav");
	model_ = new Model();
	model_->Initialize("Resources/box", "box.obj", material_);
	particle = new Particle();
	particle->Initialize({ 1.0f, 1.0f, 1.0f, 1.0f });
	sprite_ = new Sprite;
	sprite_->Initialize(material_.color);
	velocity_ = { 0,0,-0.5f };
	state = new EnemyApproach();
	material_.color = { 1.0f,1.0f,1.0f,1.0f };
	gamescene_ = gamescene;
	

	//FazeInit();

	FireLoop();

	SetCollisonAttribute(1);

	SetCollisionMask(0);
}

void Enemy::Update() {

	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});
	state->Update(this);

	/*FireTimer--;
	if (FireTimer <= 0) {
		Fire();
		FireTimer = kFireInterval;
	}*/

	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
		});

	// 範囲forでリストの全要素について回す
	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
	}

	float theta = (rotate_ / 2.0f) * (float)M_PI;
	worldTransform_.rotation_.y = theta;
	worldTransform_.UpdateMatrix();
	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();

	}
	
}

void Enemy::Draw(Camera* camera) {
	model_->Draw(worldTransform_, texture_, camera, material_,dir_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
	//sprite_->Draw(texture_,color);
	particle->Draw(texture_, material_.color, camera);

}

void Enemy::Release()
{
	Audio::SoundUnload(soundData2);
}
void Enemy::Move() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
}

void Enemy::FazeInit()
{
	//FireTimer = kFireInterval;
	FireLoop();

}

void Enemy::Fire()
{
	

		// 自キャラの座標をコピー
		Vector3 position = worldTransform_.translation_;

		// 弾の速度
		const float kBulletSpeed = -1.0f;
		Vector3 velocity(0, kBulletSpeed, kBulletSpeed);

		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		// 弾を生成し、初期化
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Init(worldTransform_.translation_, velocity);
		newBullet->SetPlayer(player_);

		// 弾を登録する
		bullets_.push_back(newBullet);


	
}
void Enemy::SetVelo(Vector3 velocity) {
	velocity_.x = velocity.x;
	velocity_.y = velocity.y;
	velocity_.z = velocity.z;
}

void Enemy::SetFireTimer(int fireTimer)
{
	FireTimer = fireTimer;
}

void Enemy::ChangeState(IEnemy* newState) {
	state = newState;
	timedCalls_.push_back(
		new TimedCall(std::bind(&Enemy::FireLoop, this), kFireInterval));
}

void Enemy::FireCount()
{
	FireTimer--;
}

void Enemy::FireLoop()
{
	Fire();
	// 発車タイマーをリセットする
	std::function<void(void)> callback = std::bind(&Enemy::FireLoop, this);

	// 時限発動イベントを生成
	TimedCall* timedCall = new TimedCall(callback, kFireInterval);

	timedCalls_.push_back(timedCall);

}

void Enemy::OnCollision()
{
	gamescene_->SetChangeScene();
}

Vector3 Enemy::GetWorldPosition() const
{
	// ワールド行列座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
