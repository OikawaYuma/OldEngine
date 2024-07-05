#pragma once
#include "IScene.h"
#include "Player/Player.h"
#include "Floor.h"
#include "Item.h"
#include "Enemy.h"
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
	Camera* camera_ = nullptr;
	Player* player_ = nullptr;
	Floor* flooar_ = nullptr;
	Item* item_ = nullptr;
	Enemy* enemy_ = nullptr;
	PostProcess* postProcess_ = nullptr;
	
};

