#include "Camera.h"
#include"WinApp.h"

void Camera::Initialize() {
	cameraTransform={ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
}

void Camera::Update(Transform transform) {
	WinApp* sWinApp = WinApp::GetInstance();
	worldmatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);;
	cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(sWinApp->kClientWidth) / float(sWinApp->kClientHeight), 0.1f, 100.0f);
	worldViewProjectionMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));


}

void Camera::Draw() {

}
