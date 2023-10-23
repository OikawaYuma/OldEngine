#include "Camera.h"
#include"WinApp.h"

void Camera::Initialize() {
	WinApp* sWinApp = WinApp::GetInstance();
	cameraTransform={ {1.0f,1.0f,1.0f},{-6.0f,0.0f,0.0f},{0.0f,20.0f,-60.0f} };
	//WinApp* sWinApp = WinApp::GetInstance();

	cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(sWinApp->GetKClientWidth()) / float(sWinApp->GetKClientHeight()), 0.1f, 100.0f);
	//worldViewProjectionMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));

}

//void Camera::Update(Transform transform) {
//	WinApp* sWinApp = WinApp::GetInstance();
//	
//	cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
//	viewMatrix = Inverse(cameraMatrix);
//	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(sWinApp->GetKClientWidth()) / float(sWinApp->GetKClientHeight()), 0.1f, 100.0f);
//	worldViewProjectionMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));
//
//
//}

void Camera::Draw() {

}
