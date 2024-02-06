#include "Slect.h"

void Slect::Init()
{
	int Width = 0;
	int Height = 0;

	input_ = Input::GetInstance();
	camera_ = new Camera;
	camera_->Initialize();
	texture_ = TextureManager::GetInstance()->StoreTexture("Resources/uvChecker.png");//画像読み込み
	PushTexture_ = TextureManager::GetInstance()->StoreTexture("Resources/circle.png");

	model_ = new Model();
	model_->Initialize("Resources/box", "box.obj", color);
	Spritemodel = new Model();
	Spritemodel->Initialize("Resources/Green", "Green.obj", color);

	PushSprite_ = new Sprite;
	PushSprite_->Initialize(color);
	SlectSprite_ = new Sprite;
	SlectSprite_->Initialize(color);



	/*worldTransform_[0].Initialize();
	worldTransform_[0].scale_ = { 1,1,1 };
	worldTransform_[0].translation_.x += 128.0f *Width;
	worldTransform_[0].translation_.y += 64.0f * Height;
	worldTransform_[0].UpdateMatrix();*/

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_.translation_.x += 128.0f * Width;
	worldTransform_.translation_.y += 64.0f * Height;
	worldTransform_.UpdateMatrix();

	SelectNumber = 0;

	PushSprite_->Initialize(color);

	PushTransform_.Initialize();
	PushTransform_.scale_ = { 1,1,1 };
	PushTransform_.translation_ = { 1024.0f,640.0f,0.0f };
	PushTransform_.UpdateMatrix();

	camera_->Initialize();



}

void Slect::Update()
{
	sceneTime++;
	for (int i = 1; i < STAGE_MAX; i++)
	{
		worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
		worldTransform_.UpdateMatrix();

		
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

void Slect::Draw()
{
	model_->Draw(worldTransform_, texture_, camera_, color);
	SlectSprite_->Draw(texture_, color);

	PushSprite_->Draw(PushTexture_, color);

}

void Slect::Release()
{
}

int Slect::GameClose()
{
	return 0;
}
