#include "GameScene.h"
#define _USE_MATH_DEFINES
#include<math.h>

void GameScene::Init()
{
	camera = new Camera;
	camera->Initialize();
	input = Input::GetInstance();
	car_ = new Car();
	car_->Init();
	floor_ = new Floor();
	floor_->Init();
	front_left_tire_ = new Front_left_tire();
	front_left_tire_->Init();
	front_right_tire_ = new Front_right_tire();
	front_right_tire_->Init();
	rear_left_tire_ = new Rear_left_tire();
	rear_left_tire_->Init();
	rear_right_tire_ = new Rear_right_tire();
	rear_right_tire_->Init();

	texture_ = TextureManager::GetInstance()->StoreTexture("Resources/tex.png");
	texture2_ = TextureManager::GetInstance()->StoreTexture("Resources/Green/Green.png");

	collisionModel_ = new Model();
	collisionModel_->Initialize("Resources/colision", "colisionCube.obj", color);

	GreenModel = new Model();
	GreenModel->Initialize("Resources/Green", "Green.obj", color);

	colisionTransform_.Initialize();//
	colisionTransform_.scale_ = { 1.0f,1.0f,1.0f };
	colisionTransform_.translation_ = { 0.0f,1.0f,100.0f };

	GreenWorldTransform_.Initialize();
	GreenWorldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	GreenWorldTransform_.translation_ = { 0.0f,1.0f,0.0f };



	testColLeftX = colisionTransform_.translation_.x - 0.5f;
	testColRight = colisionTransform_.translation_.x + 0.5f;
	testColBackZ = colisionTransform_.translation_.z + 0.5f;
	testColflontZ = colisionTransform_.translation_.z - 0.5f;

	carLeftX = car_->GetWorldTransform().x - 0.5f;
	carRightX = car_->GetWorldTransform().x + 0.5f;
	carFrontZ = car_->GetWorldTransform().z + 0.5f;
	carBackZ = car_->GetWorldTransform().z - 0.5f;




	color = { 1,1,1,1 };

	/*x1min = GreenWorldTransform_.translation_.x - GreenWorldTransform_.scale_.x / 2;
	x1max = GreenWorldTransform_.translation_.x + GreenWorldTransform_.scale_.x / 2;

	y1min = GreenWorldTransform_.translation_.y - GreenWorldTransform_.scale_.y / 2;
	y1max = GreenWorldTransform_.translation_.y + GreenWorldTransform_.scale_.y / 2;

	z1min = GreenWorldTransform_.translation_.z - GreenWorldTransform_.scale_.z / 2;
	z1max = GreenWorldTransform_.translation_.z + GreenWorldTransform_.scale_.z / 2;

	x2min = colisionTransform_.translation_.x - colisionTransform_.scale_.x / 2;
	x2max = colisionTransform_.translation_.x + colisionTransform_.scale_.x / 2;

	y2min = colisionTransform_.translation_.y - colisionTransform_.scale_.y / 2;
	y2max = colisionTransform_.translation_.y + colisionTransform_.scale_.y / 2;

	z2min = colisionTransform_.translation_.z - colisionTransform_.scale_.z / 2;
	z2max = colisionTransform_.translation_.z + colisionTransform_.scale_.z / 2;*/

}

void GameScene::Update()
{
	float theta = (car_->rotate_ / 2.0f) * (float)M_PI;
	Vector2 move = { cosf(theta),sinf(theta) };
	car_->worldTransform_.rotation_.y = theta;
	camera->cameraTransform_.translate.x = car_->worldTransform_.translation_.x;
	camera->cameraTransform_.rotate.y = car_->worldTransform_.rotation_.y / 10;

	GreenWorldTransform_.translation_ = car_->worldTransform_.translation_;

	sceneTime++;
	if (input->TriggerKey(DIK_W)) {
		moveFlag = true;
	}
	if (moveFlag) {
		camera->cameraTransform_.translate.x += car_->Speed * move.y;
		camera->cameraTransform_.translate.z += car_->Speed * move.x;
	}
	if (input->TriggerKey(DIK_SPACE)) {
		sceneNo = TITLE;
		sceneTime = 0;
	}
	if (camera->cameraTransform_.rotate.y <= -0.15f) {
		camera->cameraTransform_.rotate.y = -0.15f;
	}
	if (camera->cameraTransform_.rotate.y >= 0.15f) {
		camera->cameraTransform_.rotate.y = 0.15f;
	}
	if (input->PushKey(DIK_LSHIFT)) {
		if (camera->cameraTransform_.scale.x <= 2.0f) {
			camera->cameraTransform_.scale.x += 0.05f;
		}
		if (camera->cameraTransform_.scale.y <= 2.0f) {
			camera->cameraTransform_.scale.y += 0.05f;
		}
		if (camera->cameraTransform_.scale.z >= 0.6f) {
			camera->cameraTransform_.scale.z -= 0.02f;
		}
		/*camera->cameraTransform_.scale.x = 2.0f;
		camera->cameraTransform_.scale.y = 2.0f;
	camera->cameraTransform_.scale.z = 0.6f;*/
	}
	else
	{
		camera->cameraTransform_.translate.z = car_->GetWorldTransform().z - 25;
		camera->cameraTransform_.translate.y = 6.0f;
		camera->cameraTransform_.rotate.x = 0.125f;
		if (camera->cameraTransform_.scale.x >= 1.0f) {
			camera->cameraTransform_.scale.x -= 0.05f;
		}
		if (camera->cameraTransform_.scale.y >= 1.0f) {
			camera->cameraTransform_.scale.y -= 0.05f;
		}
		if (camera->cameraTransform_.scale.z <= 1.0f) {
			camera->cameraTransform_.scale.z += 0.02f;
		}
	}
	/*camera->cameraTransform_.scale.x = 1.0f;
	camera->cameraTransform_.scale.y = 1.0f;
	camera->cameraTransform_.scale.z = 1.0f;*/



	colisionTransform_.UpdateMatrix();
	GreenWorldTransform_.UpdateMatrix();
	camera->Update();
	floor_->Update();
	car_->Update();
	front_left_tire_->Update();
	front_right_tire_->Update();
	rear_left_tire_->Update();
	rear_right_tire_->Update();
	ImGui::Begin("Camera");
	ImGui::DragFloat3("Translate", &camera->cameraTransform_.translate.x, camera->cameraTransform_.translate.y, camera->cameraTransform_.translate.z, 1.0f);
	ImGui::DragFloat3("Translate", (float*)&camera->cameraTransform_.translate, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Rotate", (float*)&camera->cameraTransform_.rotate, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Scale", (float*)&camera->cameraTransform_.scale, 0.01f, -100.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("colision");
	ImGui::DragFloat3("Translate", &colisionTransform_.translation_.x, colisionTransform_.translation_.y, colisionTransform_.translation_.z, 1.0f);
	ImGui::DragFloat3("Translate", (float*)&colisionTransform_.translation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("rotate", (float*)&colisionTransform_.rotation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("scale", (float*)&colisionTransform_.scale_, 0.01f, -100.0f, 100.0f);
	ImGui::End();


	ImGui::Begin("Green");
	ImGui::DragFloat3("Translate", &GreenWorldTransform_.translation_.x, GreenWorldTransform_.translation_.y, GreenWorldTransform_.translation_.z, 1.0f);
	ImGui::DragFloat3("Translate", (float*)&GreenWorldTransform_.translation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("Rotate", (float*)&GreenWorldTransform_.rotation_, 0.01f, -100.0f, 100.0f);
	ImGui::DragFloat3("scale", (float*)&GreenWorldTransform_.scale_, 0.01f, -100.0f, 100.0f);
	ImGui::End();


	testColLeftX = colisionTransform_.translation_.x - 0.5f;
	testColRight = colisionTransform_.translation_.x + 0.5f;
	testColBackZ = colisionTransform_.translation_.z - 0.5f;
	testColflontZ = colisionTransform_.translation_.z + 0.5f;

	carLeftX = car_->GetWorldTransform().x - 0.5f;
	carRightX = car_->GetWorldTransform().x + 0.5f;
	carFrontZ = car_->GetWorldTransform().z + 0.5f;
	carBackZ = car_->GetWorldTransform().z - 0.5f;

	//当たり判定
	if ((testColLeftX < carRightX && testColRight>carLeftX) &&
		(testColBackZ < carFrontZ && carBackZ<testColflontZ))
	{
d		sceneNo = TITLE;
		sceneTime = 0;
	}
	//プレイヤーとブロックの当たり判定

}

void GameScene::Draw()
{
	collisionModel_->Draw(colisionTransform_, texture_, camera, color);
	GreenModel->Draw(GreenWorldTransform_, texture2_, camera, color);
	floor_->Draw(camera);
	car_->Draw(camera);
	front_left_tire_->Draw(camera);
	front_right_tire_->Draw(camera);
	rear_left_tire_->Draw(camera);
	rear_right_tire_->Draw(camera);
}

void GameScene::Release() {
	delete floor_;
	delete front_left_tire_;
	delete front_right_tire_;
	delete rear_left_tire_;
	delete rear_right_tire_;
	delete car_;
}
// ゲームを終了
int GameScene::GameClose()
{
	return false;
}
