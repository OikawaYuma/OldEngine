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



// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	DirectXCommon::D3DResourceLeakChecker leakCheck;
	WinAPI* sWinAPI = WinAPI::GetInstance();
	sWinAPI->Initialize(L"CG2");
	
	Vector4 color[20] = { 0.0f,0.0f,0.0f,1.0f };
	// Transform変数の初期化
	Transform transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Transform transformA{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	Transform transformTriangle{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Camera* camera = new Camera;
	camera->Initialize();

	WorldTransform worldTransform;
	worldTransform.Initialize();
	

	
	
	////DirectXCommon* dirX = new DirectXCommon();

	DirectXCommon* sDirctX = DirectXCommon::GetInstance();
	Input* input = new Input();
	
	sDirctX->Initialize();
	input->Initialize();
	ImGuiCommon* imGuiCommon = new ImGuiCommon;
	PSO* pso = PSO::GatInstance();
	pso->CreatePipelineStateObject();
	
	
	Triangle* mesh_[20];
	// 実験用
	bool Reset = true;


	for (int i = 0; i < 20; i++) {
		color[i] = { 1.0f,1.0f,1.0f,1.0f, };
		mesh_[i] = new Triangle();
		mesh_[i]->Initialize(camera,color[i]);
		
		
	}
	/*Sprite* sprite = new Sprite();
	Sprite* sprite2 = new Sprite();*/
	Sphere* sphere = new Sphere();

	/*Model* model = new Model();
	model->Initialize("Resources/multiMaterial","multiMaterial.obj",camera);
	
	Model* model2 = new Model();
	model2->Initialize("Resources/axis", "axis.obj",camera);*/
	
	TextureManager* textureManager = new TextureManager;
	TextureManager* textureManager2 = new TextureManager;
	TextureManager* textureManager3 = new TextureManager;
	TextureManager* textureManager4 = new TextureManager;

	textureManager2->Initialize("Resources/uvChecker.png",1);
	textureManager->Initialize("Resources/monsterBall.png",2);
	/*textureManager3->Initialize(model->modelData_.material.textureFilePath, 3);
	textureManager4->Initialize(model2->modelData_.material.textureFilePath, 4);*/
	

	for (int i = 0; i < 20; i++) {
	
		mesh_[i]->SetTextureManager(textureManager2);

	}
	/*sprite->Initialize();
	sprite2->SetTextureManager(textureManager2);
	sprite2->Initialize();
	sprite->SetTextureManager(textureManager);*/

	/*model->SetTextureManager(textureManager);
	model2->SetTextureManager(textureManager2);*/
	

	 
	sphere->SetTextureManager(textureManager2);
	sphere->Initialize(camera);

	int num = 5;

	// 
	bool useMonsterBall = true;



	MSG msg{};
	imGuiCommon->Initialize();
	

	//ウィンドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			
		}
		else {
			
			input->Update();
			// ゲームの処理の開始
			sDirctX->BeginFrame();
			
			imGuiCommon->UICreate();
			//ImGuiの更新
			imGuiCommon->Update();
			


			//カメラの更新
			camera->Update();
		/*	sprite->Update();
			sprite2->Update();*/
			
			if (Reset) {
				transform.rotate.y += 0.03f;
				//transform.translate.z += 0.03f;
			}
			for (int i = 0; i < 20; i++) {
				mesh_[i]->Draw(worldTransform,camera,color[i]);

			}
			
			if (input->PushKey(DIK_1)) {
				num++;
			}

			if (input->PushKey(DIK_2)) {
				num--;
			}
			/*model->wvpData->WVP = camera->worldViewProjectionMatrix;
			model->Draw(transform);

			model2->wvpData->WVP = camera->worldViewProjectionMatrix;
			model2->Draw(transformA);*/

			if (useMonsterBall) {
				sphere->SetTextureManager(textureManager2);
			} 
			else{
				sphere->SetTextureManager(textureManager);
			}
			sphere->Draw(transform);
			/*sprite->Draw();
			sprite2->Draw();*/
			

			ImGui::Begin("Debug");
			ImGui::Text("TransformS : x %2.2f : y %2.2f : z %2.2f", transform.scale.x, transform.scale.y, transform.scale.z);
			ImGui::Text("TransformR : x %2.2f : y %2.2f : z %2.2f", transform.rotate.x, transform.rotate.y, transform.rotate.z);
			ImGui::Text("TransformT : x %2.2f : y %2.2f : z %2.2f", transform.translate.x, transform.translate.y, transform.translate.z);
			if (ImGui::Button("Reset")) {
				if (Reset) {
					Reset = false;
					transform.translate.x = 0.0f;
					transform.translate.y = 0.0f;
					transform.translate.z = 0.0f;

					transform.rotate.x = 0;
					transform.rotate.y = 0;
					transform.rotate.z = 0;

					transform.scale.x = 1.0f;
					transform.scale.x = 1.0f;
					transform.scale.x = 1.0f;
				}
				else { Reset = true; }
			}
			ImGui::SliderFloat3("Translate", &transform.translate.x, -1.0f, 1.0f);
			ImGui::SliderFloat3("Rotate", &transform.rotate.x, -1.0f, 1.0f);
			ImGui::SliderFloat3("Scale", &transform.scale.x, -1.0f, 1.0f);


			ImGui::SliderFloat3("coler : RGB", &color[0].x, 0.0f, 1.0f);
			ImGui::ColorEdit3("color", &color[0].x);
			ImGui::DragFloat3("cameraT : ", &camera->cameraTransform.translate.x, 0.1f);
			ImGui::DragFloat3("cameraR : ", &camera->cameraTransform.rotate.x, 0.1f);
			ImGui::DragFloat3("cameraS : ", &camera->cameraTransform.scale.x, 0.1f);

			//ImGui::DragFloat3("spriteT : ", &sprite->transform_.translate.x, 0.1f);

			ImGui::DragFloat4("cT : ", &sphere->directionalLightData->color.x, 0.1f);
			ImGui::DragFloat3("caR : ", &sphere->directionalLightData->direction.x, 0.01f);
			ImGui::DragFloat("caS : ", &sphere->directionalLightData->intensity, 0.1f);
			ImGui::DragFloat3("uvs : ", &sphere->transformUv.scale.x, 0.1f);
			ImGui::DragFloat3("uvr : ", &sphere->transformUv.rotate.x, 0.1f);
			ImGui::DragFloat3("uvt : ", &sphere->transformUv.translate.x, 0.1f);

			ImGui::Checkbox("useMonsterBall", &useMonsterBall);
			ImGui::Text("%d", num);

			ImGui::End();


			//ImGuiの描画
			imGuiCommon->Draw();

			//スワップチェーン
			sDirctX->ViewChange();
		}
	}

	//出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");


	/*------------------------------------------------------------

	-------------------------------------------------------------*/
	delete sphere;
	for (int i = 0; i < 20; i++) {
		delete mesh_[i];

	}	
	
	imGuiCommon->Release();
	textureManager->Release();
	textureManager2->Release();
	textureManager4->Release();
	textureManager3->Release();
	
	delete textureManager;
	delete textureManager2;
	delete textureManager3;
	delete textureManager4;
	delete imGuiCommon;
	delete camera;
	sWinAPI->Finalize();
	delete sWinAPI;

	sDirctX->Release();
	return 0;
}