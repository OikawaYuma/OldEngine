#pragma once
#include "Vector3.h"
#include "Quaternion.h"

struct EulerTransform {
	Vector3 Tscale;
	Vector3 rotate; //Eulerでの回転
	Vector3 translate;
};
struct QuaternionTransform{
	Vector3 scale;
	Quaternion rotate;
	Vector3 translate;
};

struct Joint {
	QuaternionTransform transform; // Transform情報
};

class Skeleton {
public:
private:
};
