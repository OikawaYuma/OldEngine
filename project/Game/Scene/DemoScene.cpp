#include "DemoScene.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Loder.h"

void DemoScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	Vector3 cameraPos = camera->GetTransform().translate;
	cameraPos.y = 1;
	cameraPos.z = -15;
	camera->SetTranslate(cameraPos);
	input = Input::GetInstance();
	textureHandle = TextureManager::StoreTexture("Resources/uvChecker.png");
	textureHandle2 = TextureManager::StoreTexture("Resources/white.png");
	demoSprite = new Sprite();
	demoSprite->Init({ 0.0f,0.0f }, { 600.0f,600.0f }, { 0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, "Resources/uvChecker.png");
	material.color = { 1.0f,1.0f,1.0f,1.0f };
	material.enableLighting = false;
	worldTransform.Initialize();
	worldTransform.translation_.x = 0;
	worldTransform2.Initialize();
	worldTransform2.translation_.x = 5;
	worldTransform.UpdateMatrix();
	worldTransform2.UpdateMatrix();
	postProcess_ = new PostProcess();
	postProcess_->SetCamera(camera);
	postProcess_->Init();
	
	

	//ModelManager::GetInstance()->LoadModel("Resources/human", "sneakWalk.gltf");
	//ModelManager::GetInstance()->LoadModel("Resources/AnimatedCube", "AnimatedCube.gltf");
	//ModelManager::GetInstance()->LoadModel("Resources/ball", "ball.obj");
	Loder::LoadJsonFile("Resources", "TL_TASK", object3d_,camera);
}

void DemoScene::Update()
{
	Transform cameraNewPos = camera->GetTransform();
	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &cameraNewPos.translate.x,0.01f);
	ImGui::DragFloat3("rotate", &cameraNewPos.rotate.x, 0.01f);
	//ImGui::DragFloat3("rotatze", &object3d_[0].translate.x, 0.01f);
	ImGui::End();
	camera->SetTranslate(cameraNewPos.translate);
	camera->SetRotate(cameraNewPos.rotate);
	XINPUT_STATE joyState{};
	if (Input::GetInstance()->GetJoystickState(joyState)) {
	}

	short leftStickX = joyState.Gamepad.sThumbLX;
	if (leftStickX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		worldTransform.translation_.x -= 0.01f;
		worldTransform.rotation_.y = -rotateSize_;
	}
	if (leftStickX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		worldTransform.translation_.x += 0.01f;
		worldTransform.rotation_.y = rotateSize_;

	}

	sceneTime++;
	////カメラの更新
	camera->Update();
	demoSprite->Update();
	
	if (Input::GetInstance()->TriggerKey(DIK_A)) {
		rotateSize_ = 0.0f;
	}
	if (Input::GetInstance()->TriggerKey(DIK_D)) {
		rotateSize_ = 0.05f;
	}

	for (std::vector<Object3d*>::iterator itr = object3d_.begin(); itr != object3d_.end(); itr++) {
		(*itr)->Update();
	}

}
void DemoScene::Draw()
{
	for (std::vector<Object3d*>::iterator itr = object3d_.begin(); itr != object3d_.end(); itr++) {
		(*itr)->Draw(textureHandle, camera);
	}
}

void DemoScene::PostDraw()
{
	postProcess_->Draw();
}

void DemoScene::Release() {
}

// ゲームを終了
int DemoScene::GameClose()
{
	return false;
}
