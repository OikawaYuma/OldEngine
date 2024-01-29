#include "Colision.h"

void Colision::cubeColision(WorldTransform worldTransform1, WorldTransform worldTransform2,bool flag)
{
	float x1min = worldTransform1.translation_.x - worldTransform1.scale_.x / 2;
	float x1max = worldTransform1.translation_.x + worldTransform1.scale_.x / 2;

	float y1min = worldTransform1.translation_.y - worldTransform1.scale_.y / 2;
	float y1max = worldTransform1.translation_.y + worldTransform1.scale_.y / 2;

	float z1min = worldTransform1.translation_.z - worldTransform1.scale_.z / 2;
	float z1max = worldTransform1.translation_.z + worldTransform1.scale_.z / 2;

	float x2min = worldTransform2.translation_.x - worldTransform2.scale_.x / 2;
	float x2max = worldTransform2.translation_.x + worldTransform2.scale_.x / 2;

	float y2min = worldTransform2.translation_.y - worldTransform2.scale_.y / 2;
	float y2max = worldTransform2.translation_.y + worldTransform2.scale_.y / 2;

	float z2min = worldTransform2.translation_.z - worldTransform2.scale_.z / 2;
	float z2max = worldTransform2.translation_.z + worldTransform2.scale_.z / 2;


	if (x1min <= x2max && x1max >= x2min && y1min <= y2max && y1max >= y2min &&
		z1min <= z2max && z1max >= z2min)
	{
		flag = true;
	}
	else {
		flag = false;
	}


}
