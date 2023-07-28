#include<Windows.h>
#include"WinApp.h"
#include"DirXCommon.h"
#include"Mesh.h"
#include"ImGuiCommon.h"
#include"Camera.h"

#include"Vector4.h"
#include"Vector3.h"
#include"Matrix4x4.h"
#include"Transform.h"
#include"mathFunction.h"



// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CoInitializeEx(0,COINIT_MULTITHREADED );
	Vector4 triangle[20][3];
	Vector4 color[20] = {0.0f,0.0f,0.0f,1.0f};
	// Transform変数の初期化
	Transform transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Camera *camera = new Camera;
	camera->Initialize();
	
	for (int i = 0; i < 20; i++) {
		triangle[i][0] = { -0.9f ,0.70f + (i * -0.10f),0.0f,1.0f };
		triangle[i][1] = { -0.85f,0.80f + (i * -0.10f),0.0f,1.0f },
		triangle[i][2] = { -0.80f,0.70f + (i * -0.10f),0.0f,1.0f };
	}

	triangle[0][0] = { -1.0f,-1.0f ,0.0f,1.0f };
	triangle[0][1] = { 0.0f,1.0f ,0.0f,1.0f };
	triangle[0][2] = { 1.0f,-1.0f,0.0f,1.0f };

	WinApp *winApp = new WinApp(L"CG2");
	DirXCommon* dirX = new DirXCommon();
	ImGuiCommon* imGuiCommon = new ImGuiCommon;
	

	Mesh* mesh_[20];
	// 実験用
	Mesh* mesh2 = new Mesh();
	

	for (int i = 0; i < 20; i++) {
		color[i] = { 0.05f * i,0.0f,0.0f,1.0f, };
		mesh_[i] = new Mesh();
		mesh_[i]->Initialize( dirX,triangle[i],color[i]);
	}
	
	MSG msg{};
	imGuiCommon->Initialize(winApp, dirX);
	//ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームの処理の開始
			dirX->BeginFrame();

			//ImGuiの更新
			imGuiCommon->Update();
		
			//三角形の回転
			transform.rotate.y += 0.03f;

			//カメラの更新
			camera->Update(transform);
			
			for (int i = 0; i < 20; i++) {
				*mesh_[i]->wvpData = camera->worldViewProjectionMatrix;
				mesh_[i]->Update(dirX);
			}

			//ImGuiの描画
			imGuiCommon->Draw(dirX);

			//スワップチェーン
			dirX->ViewChange();
		}
	}

	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");


	/*------------------------------------------------------------
	
	-------------------------------------------------------------*/
	winApp->Release();

	for (int i = 0; i < 20; i++) {
		mesh_[i]->Release();
	}
	imGuiCommon->Release();
	dirX->Release( );
	CoUninitialize();
	return 0;
}