#pragma once

#include"WorldTransform.h"
class Colision
{
public:

	bool cubeCollision(WorldTransform worldTransform1, WorldTransform worldTransform2,bool flag);

	bool cllision(WorldTransform worldTransform1, WorldTransform worldTransform2, bool flag);
private:
	int isColision = 0;

};

