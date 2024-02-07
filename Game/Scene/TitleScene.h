#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Particle.h"

#include "Audio.h"

#include "TitleCar.h"
#include "Room.h"
#include "Sprite.h"
enum CameraSet {
	OneCame,
	TwoCame,
	ThreeCame
};
class TitleScene : public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;

	void FadeBlackChange();
	void CameraChange();
private:
	int sceneTime = 0;
	Camera* camera = nullptr;
	Input* input = nullptr;
	uint32_t Audiohandle_ = 0;
	bool isPlayingAudio_ = false;
	
	
	TitleCar* car_ = nullptr;
	Room* room = nullptr;
	Sprite* fadeBlack;
	float fadeColor = 0.0f;
	bool fadeBlackFlag = true;
	float rotate_;
	uint32_t texture_;
	bool isSceneChanege = false;
	uint32_t fadeBlackTimer = 0;
	uint32_t cameraSet = 0;

	uint32_t cameraTime = 0;

};

