#include "ClearScene.h"
#include "ImGuiCommon.h"
void ClearScene::Init()
{
	
	int Width = 0;
	int Height = 0;

	input_ = Input::GetInstance();
	camera = new Camera;
	camera->Initialize();
	texture_ = TextureManager::GetInstance()->StoreTexture("Resources/uvChecker.png");//画像読み込み
	camera->cameraTransform_.translate = { 2.57f,1.61f,10.69f };
	camera->cameraTransform_.rotate = { 0.13f,9.7f,0.04f };
	PushTexture_ = TextureManager::GetInstance()->StoreTexture("Resources/circle.png");
	Stage1model_ = new Model();
	Stage1model_->Initialize("Resources/box", "box.obj", color, true);
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

	
	car_ = new ClearCar();
	car_->Init();
	floor_ = new Floor();
	floor_->Init();
	skydome = new Skydome();
	skydome->Init();
	tree = new Tree();
	tree->Init();

}

void ClearScene::Update()
{
	worldTransform_.scale_ = { 0.25f,0.25f,0.25f };
	worldTransform_.UpdateMatrix();
	ImGui::Begin("Camera");

	ImGui::DragFloat3("cameratranslation_", &camera->cameraTransform_.translate.x, 0.01f);
	ImGui::DragFloat3("cameratate_", &camera->cameraTransform_.rotate.x, 0.01f);
	ImGui::End();
	sceneTime++;
	{
		XINPUT_STATE joyState;
		Input::GetInstance()->GetJoystickState(joyState);
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A && !input_->GetIsTrigger()) {
			input_->SetIsTrriger(true);
			sceneTime = 0;
			sceneNo = TITLE;
		}
		else if (!(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) && input_->GetIsTrigger()) { input_->SetIsTrriger(false); }
	}
	if (input_->TriggerKey(DIK_SPACE))
	{
		/*ステージ決定の処理
		if (PushTransform_.translation_.x == worldTransform_.translation_.x &&
			PushTransform_.translation_.y == worldTransform_.translation_.y)*/
		{
			sceneNo = TITLE;
			sceneTime = 0;
		}
	}
	floor_->Update();
	//car_->Update();
	skydome->Update();
	tree->Update();
	car_->Update();
	camera->cameraTransform_.translate.z = car_->GetWorldTransform().z + 5.69f;
	PushTransform_.UpdateMatrix();
	camera->Update();
	Vector2 size = SlectSprite_->GetSize();
	size.x += 0.2f;
	size.y += 0.1f;

	SlectSprite_->SetSize(size);
	SlectSprite_->Update();
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
	floor_->Draw(camera);
	car_->Draw(camera);
	skydome->Draw(camera);
	tree->Draw(camera);
}

void ClearScene::Release() {

}


// ゲームを終了
int ClearScene::GameClose()
{
	return false;
}