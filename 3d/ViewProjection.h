#pragma once
#include"Vector3.h"
#include"Matrix4x4.h"
#include"Transform.h"
#include"mathFunction.h"
class WinApp;
class ViewProjection
{
public:
	Transform cameraTransform;
	Matrix4x4 worldmatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;

	void Initialize();
	void Update();
	void Draw();
};

