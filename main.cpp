#include<Windows.h>
#include"WinApp.h"
#include"DirXCommon.h"
#include"TextureManager.h"
#include"Vector4.h"



// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	Vector4 pos[3][2] = {
	 { -0.9f,-0.5f,0.0f,1.0f },

	 { -0.75f,0.5f,0.0f,1.0f },

	 { -0.5f,-0.5f,0.0f,1.0f }
	};
	for (int i = 0; i < 2; i++) {
		pos[i]->x = -0.9f, -0.75f, -0.5f;
		pos[i]->y = -0.5f, 0.5f, -0.5f;
		pos[i]->z = 0.0f, 0.0f, 0.0f;
		pos[i]->w = 1.0f, 1.0f, 1.0f;
	}



	Vector4 pos2[3] = {
	 { 0.25f,-0.5f,0.0f,1.0f },

	 { 0.0f,0.5f,0.0f,1.0f },

	 { 0.75f,-0.5f,0.0f,1.0f }
	};

	WinApp *winApp = new WinApp(L"CG2");
	DirX* dirX = new DirX(winApp->hwnd_);
	TextureManager* textureManager = new TextureManager();
	TextureManager* textureManager2 = new TextureManager();
	textureManager->Initialize(winApp, dirX, pos[0]);
	textureManager2->Initialize(winApp, dirX, pos[1]);
	MSG msg{};
	//ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームの処理
			dirX->DirXUpdata();
			textureManager->Update(dirX);
			textureManager2->Update(dirX);
			dirX->ViewChange();
			
		}
	}

	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");

	winApp->Release();
	textureManager->Release();
	textureManager2->Release();
	dirX->DirXRelease( );

	return 0;
}