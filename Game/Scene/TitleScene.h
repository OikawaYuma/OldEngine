#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Input.h"
#include "Particle.h"
#include "Audio.h"
class TitleScene : public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void Release()override;
	int GameClose()override;

private:
	int sceneTime = 0;
	Camera* camera = nullptr;
	Player* player_ = nullptr;
	Input* input = nullptr;
	uint32_t Audiohandle_ = 0;
	bool isPlayingAudio_ = false;
	
	
};

