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
	ThreeCame,
	FourCame
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
	void FadeWhiteChange();
	void CameraChange();
	uint32_t GetAudio() { return Audiohandle_; };
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
	float fadeColorWhite = 0.0f;
	bool fadeBlackFlag = true;
	float rotate_;
	uint32_t texture_;
	uint32_t texture2_;
	bool isSceneChanege = false;
	uint32_t fadeBlackTimer = 0;
	uint32_t cameraSet = 0;
	float velo;
	uint32_t cameraTime = 0;
	Sprite* fadeWhite;

	uint32_t scenetimer = 0;

	Sprite* Do;
	Sprite* Ri;
	Sprite* Hu;
	Sprite* To;
	float moji = 1.0f;

	uint32_t texture3_;
	uint32_t texture4_;
	uint32_t texture5_;
	uint32_t texture6_;
	bool sceneChangeFlag = false;
};

