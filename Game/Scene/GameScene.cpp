#include "GameScene.h"
#include "ImGuiCommon.h"
#include <iostream>
bool GameScene::sceneChange = false;
void GameScene::Init()
{
	input = Input::GetInstance();
	camera = new Camera;
	camera->Initialize();
	
	collisionManager_ = new CollisionManager;
	collisionManager_->SetGameScene(this);
	player_ = new Player();
	player_->Init();
	collisionManager_->SetPlayer(player_);
	railCamera = new RailCamera();
	railCamera->Init({0,0,-30}, { 0.0f,0.0f,0.0f });
	enemy_ = new Enemy();
	enemy_->SetPlayer(player_);
	enemy_->Init(this);
	player_->SetParent(&railCamera->GetWorldTransform());
	collisionManager_->SetEnemy(enemy_);
	sprite_ = new Sprite();
	sprite_->Initialize({1.0f,1.0f,1.0f,fadeColor_ });
	sprite_->SetSize({1280.0f,720.0f});
	textureHandle_ = TextureManager::StoreTexture("Resources/Fade.png");
	
	skydome = new Skydome();
	skydome->Init();

	LoadEnemyPopData();

}

void GameScene::Update()
{
	sprite_->Update();
	if (!startFlag_) {
		fadeColor_ -= 0.02f;
		if (fadeColor_ <= 0.0f) {
			startFlag_ = true;
		}
	}

	
	else {
		ImGui::Begin("Demo");
		//ImGui::Text("bullet :%d", enemy->GetFireTimer());
		ImGui::Text("Push WASD or PAD Left プレイヤー移動");
		ImGui::Text("Push Arrow or PAD Right レティクル移動");
		ImGui::Text("Trigger Space or Pad RT 射撃");
		ImGui::Text("Trigger C 三次元カメラ移動");
		ImGui::End();
		sceneTime++;
		/*if (sceneTime >= 240) {
			sceneChange = true;
		}*/
		if (sceneChange) {
			fadeColor_ += 0.01f;
		}
		if (fadeColor_ >= 1.0f) {
			sceneNo = TITLE;
			sceneTime = 0;
			startFlag_ = false;
			sceneChange = false;
			//fadeColor_ = 0.0f;
		}
		/*if (input->TriggerKey(DIK_I)) {
			sceneNo = CLEAR;
			sceneTime = 0;

		}*/
		// デスフラグの立った弾を削除
		enemyBullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
			return false;
			});

		// デスフラグの立った弾を削除
		enemys_.remove_if([](Enemy* enemy) {
			if (enemy->IsDead()) {
				delete enemy;
				return true;
			}
			return false;
			});
		////カメラの更新
		camera->Update();
		if (input->TriggerKey(DIK_C)) {
			cameraFlag_ = true;
		}
		railCamera->Update(cameraFlag_);
		player_->Update(railCamera->camera);
		UpdateEnemyPopCommands();
		// 敵キャラの更新
		for (Enemy* enemy : enemys_) {
			enemy->Update();

			
			// enemy->Fire();
			if (enemy->GetFireTimer() >= enemy->kFireInterval) {
				assert(player_);
				// 弾の速度
				const float kBulletSpeed = 1.0f;

				Vector3 start = enemy->GetWorldPosition();
				Vector3 end = player_->GetWorldPosition();

				Vector3 diffVector;
				diffVector.x = end.x - start.x;
				diffVector.y = end.y - start.y;
				diffVector.z = end.z - start.z;

				diffVector = Normalize(diffVector);
				diffVector.x *= kBulletSpeed;
				diffVector.y *= kBulletSpeed;
				diffVector.z *= kBulletSpeed;

				Vector3 velocity(diffVector.x, diffVector.y, diffVector.z);

				// 速度ベクトルを自機の向きに合わせて回転させる
				velocity = TransformNormal(velocity, enemy->GetWorldTransform().matWorld_);

				// 弾を生成し、初期化
				EnemyBullet* newBullet = new EnemyBullet();
				newBullet->Init(enemy->GetWorldTransform().translation_, velocity);
				newBullet->SetPlayer(player_);
				// 弾を登録する
				enemyBullets_.push_back(newBullet);
				enemy->SetFireTimer(0);
			}
		}

		// 弾更新
		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Update();
		}
		if (cameraFlag_ == false) {
			collisionManager_->CheckAllCollision();
		}
	}
}
void GameScene::Draw()
{
	skydome->Draw(railCamera->camera);
	if (startFlag_) {
		
		player_->Draw(railCamera->camera);
		for (Enemy* enemy : enemys_) {
			enemy->Draw(railCamera->camera);
		}

		// 敵弾の描画
		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Draw(railCamera->camera);
		}
	}
	player_->DrawUI();
	sprite_->Draw(textureHandle_,{1.0f,1.0f,1.0f, fadeColor_ });
	
}

void GameScene::Release() {
	delete player_;
	delete enemy_;
}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}

void GameScene::SetChangeScene()
{
	sceneChange = true;
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet)
{
	// リストに登録
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::LoadEnemyPopData()
{

	// ファイルを開く
	std::ifstream file;
	file.open("enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands()
{


	// 待機処理
	if (isRespown) {
		respownTimer_--;
		if (respownTimer_ <= 0) {
			//待機完了
			isRespown = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変婚して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			enemyAppear({ x, y, z });

		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());
			// 待機開始
			isRespown = true;
			respownTimer_ = waitTime;

			// コマンドループを抜ける
			break;

		}


	}


}

void GameScene::enemyAppear(Vector3 translation)
{

	// 敵キャラの生成
	Enemy* newEnemy = new Enemy();
	// 敵キャラの初期化
	newEnemy->Init(this);
	// 敵キャラに自キャラのアドレスを渡す
	newEnemy->SetPlayer(player_);
	enemys_.push_back(newEnemy);
}
