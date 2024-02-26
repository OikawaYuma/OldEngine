#pragma once
#include "Camera.h"
#include "WorldTransform.h"
#include "Input.h"

enum cameraTragetPos {
	TargetOne,
	TargetTwo,
	TargetThree,
	TargetFour
};
class RailCamera
{
public:
	void Init(const Vector3& pos,const Vector3& rot);
	void Update(bool flag);
	const WorldTransform& GetWorldTransform() { return worldTransform_; };

	Vector3 GetToDire() { return toDire; }
	Camera* camera = nullptr;
private:
	WorldTransform worldTransform_;
	Input* input_ = nullptr;
	std::vector<Vector3> constrolPoint_;
	float t;

	Vector3 toDire;
};

