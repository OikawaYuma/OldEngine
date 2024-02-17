#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "Input.h"
#include "Particle.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "../Skydome.h"
#include "RailCamera.h"
class GameScene :public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;
	static void SetChangeScene();
	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name= "enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);
	// 弾リストを取得
	const std::list<EnemyBullet*>& Getbullet() const { return enemyBullets_; }
	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	void enemyAppear(Vector3 translation);

	private:
	Input* input = nullptr;
	int sceneTime = 0;
	Camera* camera = nullptr;
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemys_;
	//弾
	EnemyBullet* enemybullet_ = nullptr;
	// 弾リスト
	std::list<EnemyBullet*> enemyBullets_;
	Sprite* sprite_ = nullptr;
	float fadeColor_ = 1.0f;
	uint32_t textureHandle_;
	bool startFlag_ = false;
	static bool sceneChange;
	CollisionManager* collisionManager_ = nullptr;
	RailCamera* railCamera = nullptr;
	Skydome* skydome = nullptr;

	// スポーンフラグ
	bool isRespown = true;

	//スポーンタイマー
	int respownTimer_ = 0;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;
};

