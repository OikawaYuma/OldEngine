#include "TitleScene.h"
#include "ImGuiCommon.h"


void TitleScene::Init()
{
	input = Input::GetInstance();
	title_ = new Sprite();
	title_->Initialize({ 1.0f, 1.0f, 1.0f, 1.0f });
	title_->SetSize({ 1280.0f, 720.0f });
	push_ = new Sprite();
	push_->Initialize({ 1.0f, 1.0f, 1.0f, 1.0f });
	push_->SetSize({ 1280.0f, 720.0f });
	sprite_ = new Sprite();
	sprite_->Initialize({ 1.0f, 1.0f, 1.0f, fadeColor_ });
	sprite_->SetSize({1280.0f, 720.0f});
	textureHandle = TextureManager::StoreTexture("Resources/Fade.png");
	textureHandle2 = TextureManager::StoreTexture("Resources/Title.png");
	textureHandle3 = TextureManager::StoreTexture("Resources/Push.png");
}

void TitleScene::Update()
{
	title_->Update();
	sprite_->Update();
	push_->Update();
	if (!startFlag_) {
		fadeColor_ -= 0.02f;
		if (fadeColor_ <= 0.0f) {
			startFlag_ = true;
		}
	}

	else {
		sceneTime++;
		if (input->TriggerKey(DIK_I)) {
			sceneChange = true;
		}
		if (sceneChange) {
			fadeColor_ += 0.01f;
		}
		if (fadeColor_ >= 1.0f) {
			sceneNo = STAGE;
			sceneTime = 0;
			startFlag_ = false;
			sceneChange = false;
			//fadeColor_ = 0.0f;
		}

		if (!pushFlag) {
			pushColor_ -= 0.02f;
			if (pushColor_ <= 0.0f) {
				pushFlag = true;
				pushColor_ = 0.0f;
			}
		}
		else if (pushFlag) {
			pushColor_ += 0.02f;
			if (pushColor_ >= 1.0f) {
				pushFlag = false;
				pushColor_ = 1.0f;
			}
		}
	}
	
}
void TitleScene::Draw()
{

	title_->Draw(textureHandle2, { 1.0f, 1.0f, 1.0f, 1.0f });
	push_->Draw(textureHandle3, { 1.0f, 1.0f, 1.0f, pushColor_ });
	sprite_->Draw(textureHandle, { 1.0f, 1.0f, 1.0f, fadeColor_ });
}

void TitleScene::Release() {

}

// ゲームを終了
int TitleScene::GameClose()
{
	return false;
}