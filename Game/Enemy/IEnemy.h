#pragma once
class Enemy;
class IEnemy
{
public:
	virtual void Update(Enemy* pEnemy) = 0;
};

