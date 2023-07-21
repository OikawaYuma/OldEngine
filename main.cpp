#include<Windows.h>
#include"WinApp.h"
#include"DirXCommon.h"
#include"Mesh.h"
#include"ImGuiCommon.h"

#include"Vector4.h"
#include"Vector3.h"
#include"Matrix4x4.h"
#include"Transform.h"
#include"mathFunction.h"



// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CoInitializeEx(0,COINIT_MULTITHREADED );
	Vector4 pos[20][3];
	Vector4 color[20] = {0.0f,0.0f,0.0f,1.0f};
	// Transform変数の初期化
	Transform transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Transform cameraTransform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
	
	for (int i = 0; i < 20; i++) {
		pos[i][0] = { -0.9f ,0.70f + (i * -0.10f),0.0f,1.0f };
		pos[i][1] = { -0.85f,0.80f + (i * -0.10f),0.0f,1.0f },
		pos[i][2] = { -0.80f,0.70f + (i * -0.10f),0.0f,1.0f };
	}

	pos[0][0] = { -1.0f,-1.0f ,0.0f,1.0f };
	pos[0][1] = { 0.0f,1.0f ,0.0f,1.0f };
	pos[0][2] = { 1.0f,-1.0f,0.0f,1.0f };

	WinApp *winApp = new WinApp(L"CG2");
	DirX* dirX = new DirX(winApp->hwnd_);
	ImGuiCommon* imGuiCommon = new ImGuiCommon;
	

	Mesh* triangle[20];
	Mesh* triangle2 = new Mesh();
	

	for (int i = 0; i < 20; i++) {
		color[i] = { 0.05f * i,0.0f,0.0f,1.0f, };
		triangle[i] = new Mesh();
		triangle[i]->Initialize(winApp, dirX, pos[i],color[i]);
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
		
			imGuiCommon->Update();
		
			// ゲームの処理
			dirX->DirXUpdata();
			
			transform.rotate.y += 0.03f;
			Matrix4x4 worldmatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);;
			Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
			Matrix4x4 viewMatrix = Inverse(cameraMatrix);
			Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(winApp->kClientWidth) / float(winApp->kClientHeight), 0.1f, 100.0f);
			Matrix4x4 worldViewProjectionMatrix = Multiply(worldmatrix, Multiply(viewMatrix, projectionMatrix));
			
			
			for (int i = 0; i < 20; i++) {
				*triangle[i]->wvpData = worldViewProjectionMatrix;
				triangle[i]->Update(dirX);
			}
			imGuiCommon->Draw(dirX);
			dirX->ViewChange();
		}
	}

	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");

	winApp->Release();
	for (int i = 0; i < 20; i++) {
		triangle[i]->Release();
	}
	imGuiCommon->Release();
	dirX->DirXRelease( );
	CoUninitialize();
	return 0;
}