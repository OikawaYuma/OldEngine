#pragma once
#include"Vector3.h"
#include"Matrix4x4.h"
#include"Transform.h"
#include"mathFunction.h"
#include <numbers>

class Camera
{
public:
	void Initialize();
	void Update();
	void Draw();

	Transform GetTransform() { return transform_; }
	Matrix4x4 GetCameraMatrix() { return cameraMatrix_; }
	Matrix4x4 GetViewMatrix() { return viewMatrix_; }
	Matrix4x4 GetProjectionMatrix() { return projectionMatrix_; }
private:
	Transform transform_;
	Matrix4x4 worldmatrix_;
	Matrix4x4 cameraMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;

};

