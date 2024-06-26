#pragma once
#include "IScene.h"
#include "Player/Player.h"
#include "PostProcess.h"

#include <vector>


class GameScene :public IScene
{
public:
	void Init() override;
	void Update()override;
	void Draw()override;
	void PostDraw()override;
	void Release()override;
	int GameClose()override;
private:
	std::unique_ptr<Camera> camera_;
	std::unique_ptr<Player> player_;
	PostProcess* postProcess_ = nullptr;
	
};

