#include "ClearScene.h"

void ClearScene::Init()
{
	
	int Width = 0;
	int Height = 0;

	input_ = Input::GetInstance();
	camera_ = new Camera;
	camera_->Initialize();
	texture_ = TextureManager::GetInstance()->StoreTexture("Resources/uvChecker.png");//画像読み込み

	PushTexture_ = TextureManager::GetInstance()->StoreTexture("Resources/circle.png");
	Stage1model_ = new Model();
	Stage1model_->Initialize("Resources/box", "box.obj", color);
	//Pushmodel_->Initialize("Resources/")
	SlectSprite_ = new Sprite;
	SlectSprite_->Initialize(color);

	SelectNumber = 0;
	PushSprite_ = new Sprite;
	PushSprite_->Initialize(color);

	PushTransform_.Initialize();
	PushTransform_.scale_ = { 0.25f,0.25f,0.25f };
	PushTransform_.translation_ = { 640.0f,320.0f,0.0f };
	PushTransform_.UpdateMatrix();

	camera_->Initialize();


}

void ClearScene::Update()
{
	worldTransform_.scale_ = { 0.25f,0.25f,0.25f };
	worldTransform_.UpdateMatrix();

	sceneTime++;

	if (input_->TriggerKey(DIK_SPACE))
	{
		/*ステージ決定の処理
		if (PushTransform_.translation_.x == worldTransform_.translation_.x &&
			PushTransform_.translation_.y == worldTransform_.translation_.y)*/
		{
			sceneNo = STSGE1;
			sceneTime = 0;
		}
	}


	PushTransform_.UpdateMatrix();
	camera_->Update();


	if (!SelectLock)
	{
		if (input_->TriggerKey(DIK_W))
		{
			PushTransform_.translation_.y = -50;
		}

		if (input_->TriggerKey(DIK_S))
		{
			PushTransform_.translation_.y = +50;
		}

		if (input_->TriggerKey(DIK_A))
		{
			PushTransform_.translation_.x = -50;
		}

		if (input_->TriggerKey(DIK_D))
		{
			PushTransform_.translation_.x = +50;
		}
	}

}
void ClearScene::Draw()
{
		Stage1model_->Draw(worldTransform_, texture_, camera_, color);
		SlectSprite_->Draw(texture_, color);
	PushSprite_->Draw(PushTexture_,color);
}

void ClearScene::Release() {

}


// ゲームを終了
int ClearScene::GameClose()
{
	return false;
}