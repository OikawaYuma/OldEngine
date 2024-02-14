#include "GameScene.h"

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
	
	enemy_ = new Enemy();
	enemy_->Init(this);
	collisionManager_->SetEnemy(enemy_);
	sprite_ = new Sprite();
	sprite_->Initialize({1.0f,1.0f,1.0f,fadeColor_ });
	textureHandle_ = TextureManager::StoreTexture("Resources/Fade.png");
	

}

void GameScene::Update()
{
	if (!startFlag_) {
		fadeColor_ -= 0.02f;
		if (fadeColor_ <= 0.0f) {
			startFlag_ = true;
		}
	}

	else {
		sceneTime++;
		/*if (sceneTime >= 240) {
			sceneChange = true;
		}*/
		if (sceneChange) {
			fadeColor_ += 0.01f;
		}
		if (fadeColor_ >= 1.0f) {
			sceneNo = CLEAR;
			sceneTime = 0;
			startFlag_ = false;
			sceneChange = false;
			//fadeColor_ = 0.0f;
		}
		/*if (input->TriggerKey(DIK_I)) {
			sceneNo = CLEAR;
			sceneTime = 0;

		}*/

		////カメラの更新
		camera->Update();

		player_->Update();
		enemy_->Update();
		collisionManager_->CheckAllCollision();
	}
}
void GameScene::Draw()
{
	player_->Draw(camera);
	enemy_->Draw(camera);
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
