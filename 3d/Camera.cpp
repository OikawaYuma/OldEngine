#include "Camera.h"
#include"WinAPI.h"

void Camera::Initialize() {
	WinAPI* sWinAPI = WinAPI::GetInstance();
	cameraTransform={ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,00.0f,-15.0f} };
	//WinAPI* sWinAPI = WinAPI::GetInstance();

	cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(sWinAPI->GetKClientWidth()) / float(sWinAPI->GetKClientHeight()), 0.1f, 100.0f);
	//worldCameraMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));

}

void Camera::Update() {
	WinAPI* sWinAPI = WinAPI::GetInstance();
	
	cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(sWinAPI->GetKClientWidth()) / float(sWinAPI->GetKClientHeight()), 0.1f, 100.0f);
	worldViewProjectionMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));


}

void Camera::Draw() {

}
