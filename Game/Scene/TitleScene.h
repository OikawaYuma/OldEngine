#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Input.h"
#include "Particle.h"
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
	Input* input = nullptr;
	
};

