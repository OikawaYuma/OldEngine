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
	PushSprite_ = new Sprite;
	SlectSprite_ = new Sprite;
	SlectSprite_->Initialize(color);



	/*worldTransform_[0].Initialize();
	worldTransform_[0].scale_ = { 1,1,1 };
	worldTransform_[0].translation_.x += 128.0f *Width;
	worldTransform_[0].translation_.y += 64.0f * Height;
	worldTransform_[0].UpdateMatrix();*/

	SelectNumber = 0;

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
		//ステージ決定の処理
		if (PushTransform_.translation_.x == worldTransform_.translation_.x &&
			PushTransform_.translation_.y == worldTransform_.translation_.y)
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