#include "EnemyApproach.h"
#include"EnemyLeave.h"
void EnemyApproach::Update(Enemy* pEnemy)
{
	pEnemy->SetVelo({ 0, 0, -0.2f });
	pEnemy->Move();
	/*pEnemy->FireCount();
	if (pEnemy->GetFireTimer() <= 0) {
		pEnemy->Fire();
		pEnemy->SetFireTimer(Enemy::kFireInterval);
	}*/


	if (pEnemy->GetTranslation().z <= 0) {
		pEnemy->ChangeState(new EnemyLeave());
	}
}
