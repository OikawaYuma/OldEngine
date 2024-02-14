#include "EnemyLeave.h"

void EnemyLeave::Update(Enemy* pEnemy)
{
	pEnemy->SetVelo({ -0.2f, 0.2f, -0.2f });
	pEnemy->Move();
	///*pEnemy->FireCount();
	//if (pEnemy->GetFireTimer() <= 0) {
	//	pEnemy->Fire();
	//	pEnemy->SetFireTimer(Enemy::kFireInterval);
	//}*/
}
