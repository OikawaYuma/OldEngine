#include "GameManager.h"
#include <Windows.h>
#include "WinAPI.h"
#include "DirectXCommon.h"
#include "PSO.h"
#include "Input.h"
#include "Mesh.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Sphere.h"
#include "Model.h"
#include "Triangle.h"

#include "VertexData.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Transform.h"
#include "mathFunction.h"

// コンストラクタ
GameManager::GameManager() {
	// 各シーンの排列
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[STAGE] = std::make_unique<GameScene>();
	sceneArr_[CLEAR] = std::make_unique<ClearScene>();

	// 初期シーンの設定
	//sceneNo_ = TITLE; //GameManagerのクラスにISceneを継承させて触れるようにしているため正しいかは怪しい
	//input_ = Input::GetInstance();
}

GameManager::~GameManager() {}

const char kWindowTitle[] = "LE2B_05_オイカワユウマ";

int GameManager::Run() {
	
	DirectXCommon::D3DResourceLeakChecker leakCheck;
	WinAPI* sWinAPI = WinAPI::GetInstance();
	sWinAPI->Initialize(L"CG2");

	WorldTransform worldTransform;
	worldTransform.Initialize();

	DirectXCommon* sDirctX = DirectXCommon::GetInstance();
	Input* input = new Input();

	sDirctX->Initialize();
	input->Initialize();

	PSO* pso = PSO::GatInstance();
	pso->CreatePipelineStateObject();
	// ウィンドウの×ボタンが押されるまでループ
	//ウィンドウの×ボタンが押されるまでループ
	while (true)  // ゲームループ
	{
		// Windowsのメッセージ処理
		if (sWinAPI->ProcessMessage()) {
			// ゲームループを抜ける
			break;
		}
		// ゲームの処理の開始
		sDirctX->BeginFrame();

		ImGui::Begin("kakunin");
		ImGui::Text("%d", IScene::GetSceneNo());
		ImGui::End();

		//// キー入力を受け取る
		//memcpy(preKeys, keys, 256);
		//Novice::GetHitKeyStateAll(keys);

		// シーンのチェック
		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

		// シーン変更チェック
		if (prevSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Init();
		}

		///
		/// ↓更新処理ここから
		///
		sceneArr_[currentSceneNo_]->Update(); // シーンごとの更新処理

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		sceneArr_[currentSceneNo_]->Draw();


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		//スワップチェーン
		sDirctX->ViewChange();

		// ESCキーが押されたらループを抜ける
		if (sceneArr_[currentSceneNo_]->GameClose()) {
			break;
		}
	}

	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");


	/*------------------------------------------------------------

	-------------------------------------------------------------*/

	sWinAPI->Finalize();
	//delete sWinAPI;
	sDirctX->Release();

	return 0;
}