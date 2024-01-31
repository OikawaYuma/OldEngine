#pragma once
#include "Collider.h"
#include<list>
class GameScene;
class Player;
class Enemy;
class CollisionManager {
public:
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	void CheckAllCollision();

	void SetGameScene(GameScene* gamescene) { gameScene_ = gamescene; }
	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

private:
	GameScene* gameScene_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;

	// 敵キャラ
	Enemy* enemy_ = nullptr;


};

