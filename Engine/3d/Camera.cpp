#include "Camera.h"
#include"WinAPI.h"

void Camera::Initialize() {
	cameraTransform_={ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-80.0f} };
	//WinAPI* sWinAPI = WinAPI::GetInstance();

	cameraMatrix_ = MakeAffineMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	viewMatrix_ = Inverse(cameraMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(WinAPI::kClientWidth_) / float(WinAPI::kClientHeight_), 0.1f, 100.0f);
	//worldCameraMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));
	worldViewProjectionMatrix_ = Multiply(worldmatrix_, Multiply(viewMatrix_, projectionMatrix_));
}

void Camera::Update() {
	cameraMatrix_ = MakeAffineMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	viewMatrix_ = Inverse(cameraMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(WinAPI::kClientWidth_) / float(WinAPI::kClientHeight_), 0.1f, 100.0f);
	worldViewProjectionMatrix_ = Multiply(worldmatrix_, Multiply(viewMatrix_, projectionMatrix_));


}

void Camera::Draw() {

}
