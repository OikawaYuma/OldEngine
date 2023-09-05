#include <Windows.h>
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Mesh.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"
#include "Camera.h"

#include "VertexData.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Transform.h"
#include "mathFunction.h"



// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//VertexData triangle[20][3];
	//VertexData triangle1[3];
	//Vector4 color[20] = { 0.0f,0.0f,0.0f,1.0f };
	//// Transform変数の初期化
	//Transform transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	//Camera* camera = new Camera;
	//camera->Initialize();

	//for (int i = 0; i < 20; i++) {
	//	triangle[i][0].position = { -0.9f ,0.70f + (i * -0.10f),0.0f,1.0f };
	//	triangle[i][0].texcorrd = { 0.0f,1.0f };

	//	triangle[i][1].position = { -0.85f,0.80f + (i * -0.10f),0.0f,1.0f },
	//	triangle[i][0].texcorrd = { 0.5f,0.0f };

	//	triangle[i][2].position = { -0.80f,0.70f + (i * -0.10f),0.0f,1.0f };
	//	triangle[i][0].texcorrd = { 1.0f,1.0f };
	//}

	//triangle[0][0].position = { -1.0f,-1.0f ,0.0f,1.0f };
	//triangle[0][0].texcorrd = { 0.0f,1.0f };
	//triangle[0][1].position = { 0.0f,1.0f ,0.0f,1.0f };
	//triangle[0][0].texcorrd = { 0.5f,0.0f };
	//triangle[0][2].position = { 1.0f,-1.0f,0.0f,1.0f };
	//triangle[0][0].texcorrd = { 1.0f,1.0f };


	//triangle1[0].position = { -0.5f,-0.5f ,0.0f,1.0f };
	//triangle1[0].texcorrd = { 0.0f,1.0f };
	//triangle1[1].position = { 0.0f,0.5f ,0.0f,1.0f };
	//triangle1[1].texcorrd = { 0.5f,0.0f };
	//triangle1[2].position = { 0.5f,-0.5f,0.0f,1.0f };
	//triangle1[2].texcorrd = { 1.0f,1.0f };

	//


	WinApp* swinApp = WinApp::GetInstance();
	swinApp->Initialize(L"CG2");
	////DirectXCommon* dirX = new DirectXCommon();

	//DirectXCommon* dirX = new DirectXCommon();

	//dirX->Initialize();
	//ImGuiCommon* imGuiCommon = new ImGuiCommon;

	//Mesh* mesh_[20];

	//// 実験用
	//Mesh* mesh2 = new Mesh();

	//TextureManager* textureManager = new TextureManager;
	//textureManager->SetDirectXCommon(dirX);
	//textureManager->Initialize( "Resources/uvChecker.png");
	//bool Reset = true;


	//for (int i = 0; i < 20; i++) {
	//	color[i] = { 0.05f * i,0.0f,0.0f,1.0f, };
	//	mesh_[i] = new Mesh();
	//	mesh_[i]->SetDirectXCommon(dirX);
	//	mesh_[i]->Initialize( triangle[i], color[i]);
	//	mesh_[i]->SetTextureManager(textureManager);
	//	
	//}
	//


	

	MSG msg{};
	//imGuiCommon->Initialize(winApp, dirX);


	//ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//// ゲームの処理の開始
			//dirX->BeginFrame();

			////ImGuiの更新
			//imGuiCommon->Update();



			////カメラの更新
			//camera->Update(transform);
			//if (Reset) {
			//	transform.rotate.y += 0.03f;
			//}
			//for (int i = 0; i < 20; i++) {
			//	*mesh_[i]->wvpData = camera->worldViewProjectionMatrix;
			//	mesh_[i]->Update( color[i]);
			//
			//}

			//ImGui::Begin("Debug");
			//ImGui::Text("TransformS : x %2.2f : y %2.2f : z %2.2f", transform.scale.x, transform.scale.y, transform.scale.z);
			//ImGui::Text("TransformR : x %2.2f : y %2.2f : z %2.2f", transform.rotate.x, transform.rotate.y, transform.rotate.z);
			//ImGui::Text("TransformT : x %2.2f : y %2.2f : z %2.2f", transform.translate.x, transform.translate.y, transform.translate.z);
			//if (ImGui::Button("Reset")) {
			//	if (Reset) {
			//		Reset = false;
			//		transform.translate.x = 0.0f;
			//		transform.translate.y = 0.0f;
			//		transform.translate.z = 0.0f;

			//		transform.rotate.x = 0;
			//		transform.rotate.y = 0;
			//		transform.rotate.z = 0;

			//		transform.scale.x = 1.0f;
			//		transform.scale.x = 1.0f;
			//		transform.scale.x = 1.0f;
			//	}
			//	else { Reset = true; }
			//}
			//ImGui::SliderFloat3("Translate", &transform.translate.x, -1.0f, 1.0f);
			//ImGui::SliderFloat3("Rotate", &transform.rotate.x, -1.0f, 1.0f);
			//ImGui::SliderFloat3("Scale", &transform.scale.x, -1.0f, 1.0f);


			//ImGui::SliderFloat3("coler : RGB", &color[0].x, 0.0f, 1.0f);
			//ImGui::ColorEdit3("color", &color[0].x);
			//ImGui::DragFloat3("cameraT : ", &camera->cameraTransform.translate.x, 0.1f);
			//ImGui::DragFloat3("cameraR : ", &camera->cameraTransform.rotate.x, 0.1f);
			//ImGui::DragFloat3("cameraS : ", &camera->cameraTransform.scale.x, 0.1f);



			//ImGui::End();


			////ImGuiの描画
			//imGuiCommon->Draw(dirX);

			////スワップチェーン
			//dirX->ViewChange();
		}
	}

	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");


	/*------------------------------------------------------------

	-------------------------------------------------------------*/
	//winApp->Release();

	//for (int i = 0; i < 20; i++) {
	//	mesh_[i]->Release();
	//}
	//imGuiCommon->Release();
	//dirX->Release();
	//CoUninitialize();
	return 0;
}