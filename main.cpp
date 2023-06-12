#include<Windows.h>
#include"WinApp.h"
#include"DirXCommon.h"
#include"TextureManager.h"
#include"Vector4.h"



// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	Vector4 pos[20][3];
	for (int i = 0; i < 20; i++) {
		pos[i][0] = { -0.9f,0.70f+(i*-0.10f),0.0f,1.0f };
		
		pos[i][1] = { -0.85f,0.80f + (i * -0.10f),0.0f,1.0f },

		pos[i][2] = { -0.80f,0.70f + (i * -0.10f),0.0f,1.0f };
	}

	WinApp *winApp = new WinApp(L"CG2");
	DirX* dirX = new DirX(winApp->hwnd_);
	TextureManager* textureManager[20];
	TextureManager* textureManager2 = new TextureManager();
	

	for (int i = 0; i < 20; i++) {
		textureManager[i] = new TextureManager();
		textureManager[i]->Initialize(winApp, dirX, pos[i]);
	}
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
			for (int i = 0; i < 20; i++) {
				textureManager[i]->Update(dirX);
			}
		
			dirX->ViewChange();
			
		}
	}

	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");

	winApp->Release();
	for (int i = 0; i < 20; i++) {
		textureManager[i]->Release();
	}
	dirX->DirXRelease( );

	return 0;
}