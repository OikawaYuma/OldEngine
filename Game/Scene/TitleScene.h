#pragma once
#include "IScene.h"
#include "Triangle.h"
#include "WorldTransform.h"
#include "Player.h"
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
	Triangle* mesh_[20];
	Vector4 color[20] = { 0.0f,0.0f,0.0f,1.0f };
	Camera* camera = nullptr;
	Transform transformTriangle;
	WorldTransform worldTransform;
	uint32_t TriangleTex;
	Player* player_ = nullptr;
};

