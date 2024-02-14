#include "ClearScene.h"

void ClearScene::Init()
{
	input = Input::GetInstance();
	sprite_ = new Sprite();
	sprite_->Initialize({ 1.0f,1.0f,1.0f,fadeColor_ });
	textureHandle_ = TextureManager::StoreTexture("Resources/Fade.png");
}

void ClearScene::Update()
{

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
			sceneNo = TITLE;
			sceneTime = 0;
			startFlag_ = false;
			sceneChange = false;
			//fadeColor_ = 0.0f;
		}
	}
}
void ClearScene::Draw()
{
	sprite_->Draw(textureHandle_, { 1.0f,1.0f,1.0f, fadeColor_ });
}

void ClearScene::Release() {

}


// ゲームを終了
int ClearScene::GameClose()
{
	return false;
}