#include <Windows.h>
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Mesh.h"
#include "ImGuiCommon.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Sphere.h"
#include "Model.h"

#include "VertexData.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Transform.h"
#include "mathFunction.h"



// Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CoInitializeEx(0, COINIT_MULTITHREADED);
	VertexData triangle[20][6];
	VertexData triangle1[6];
	Vector4 color[20] = { 0.0f,0.0f,0.0f,1.0f };
	// Transform変数の初期化
	Transform transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Transform transformA{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Camera* camera = new Camera;
	camera->Initialize();

	for (int i = 0; i < 20; i++) {
		triangle[i][0].position = { -0.9f ,0.70f + (i * -0.10f),0.0f,1.0f };
		triangle[i][0].texcorrd = { 0.0f,1.0f };

		triangle[i][1].position = { -0.85f,0.80f + (i * -0.10f),0.0f,1.0f },
		triangle[i][1].texcorrd = { 0.5f,0.0f };

		triangle[i][2].position = { -0.80f,0.70f + (i * -0.10f),0.0f,1.0f };
		triangle[i][2].texcorrd = { 1.0f,1.0f };
	}

	triangle[0][0].position = { -1.0f,-1.0f ,0.0f,1.0f };
	triangle[0][0].texcorrd = { 0.0f,1.0f };
	triangle[0][1].position = { 0.0f,1.0f ,0.0f,1.0f };
	triangle[0][1].texcorrd = { 0.5f,0.0f };
	triangle[0][2].position = { 1.0f,-1.0f,0.0f,1.0f };
	triangle[0][2].texcorrd = { 1.0f,1.0f };


	triangle1[0].position = { -0.5f,-0.5f ,0.0f,1.0f };
	triangle1[0].texcorrd = { 0.0f,1.0f };
	triangle1[1].position = { 0.0f,0.5f ,0.0f,1.0f };
	triangle1[1].texcorrd = { 0.5f,0.0f };
	triangle1[2].position = { 0.5f,-0.5f,0.0f,1.0f };
	triangle1[2].texcorrd = { 1.0f,1.0f };

	for (int i = 0; i < 20; i++) {
		triangle[i][3].position = { -0.9f ,0.70f + (i * -0.10f),0.0f,1.0f };
		triangle[i][3].texcorrd = { 0.0f,1.0f };

		triangle[i][4].position = { -0.85f,0.80f + (i * -0.10f),0.0f,1.0f },
		triangle[i][4].texcorrd = { 0.5f,0.0f };

		triangle[i][5].position = { -0.80f,0.70f + (i * -0.10f),0.0f,1.0f };
		triangle[i][5].texcorrd = { 1.0f,1.0f };
	}

	triangle[0][3].position = { -1.0f,-1.0f ,1.0f,1.0f };
	triangle[0][3].texcorrd = { 0.0f,1.0f };
	triangle[0][4].position = { 0.0f,0.0f ,0.0f,1.0f };
	triangle[0][4].texcorrd = { 0.5f,0.0f };
	triangle[0][5].position = { 1.0f,-1.0f,-1.0f,1.0f };
	triangle[0][5].texcorrd = { 1.0f,1.0f };


	triangle1[3].position = { -0.5f,-0.5f ,0.5f,1.0f };
	triangle1[3].texcorrd = { 0.0f,1.0f };
	triangle1[4].position = { 0.0f,0.0f ,0.0f,1.0f };
	triangle1[4].texcorrd = { 0.5f,0.0f };
	triangle1[5].position = { 0.5f,-0.5f,-0.5f,1.0f };
	triangle1[5].texcorrd = { 1.0f,1.0f };

	

	
	WinApp* sWinApp = WinApp::GetInstance();
	sWinApp->Initialize(L"CG2");
	////DirectXCommon* dirX = new DirectXCommon();

	DirectXCommon* sDirctX = DirectXCommon::GetInstance();
	Input* input = new Input();
	
	sDirctX->Initialize();
	input->Initialize();
	ImGuiCommon* imGuiCommon = new ImGuiCommon;

	
	Mesh* mesh_[20];
	// 実験用
	Mesh* mesh2 = new Mesh();

	
	bool Reset = true;


	for (int i = 0; i < 20; i++) {
		color[i] = { 1.0f,1.0f,1.0f,1.0f, };
		mesh_[i] = new Mesh();
		mesh_[i]->Initialize( triangle[i], color[i]);
		
		
	}
	Sprite* sprite = new Sprite();
	Sprite* sprite2 = new Sprite();
	Sphere* sphere = new Sphere();

	Model* model = new Model();
	model->Initialize("Resources/multiMaterial","multiMaterial.obj",camera);
	
	Model* model2 = new Model();
	model2->Initialize("Resources/floor", "floor.obj",camera);
	
	TextureManager* textureManager = new TextureManager;
	TextureManager* textureManager2 = new TextureManager;
	TextureManager* textureManager3 = new TextureManager;
	TextureManager* textureManager4 = new TextureManager;

	textureManager2->Initialize("Resources/uvChecker.png",1);
	textureManager->Initialize("Resources/monsterBall.png",2);
	textureManager3->Initialize(model->modelData_.material.textureFilePath, 3);
	textureManager4->Initialize(model2->modelData_.material.textureFilePath, 4);
	

	for (int i = 0; i < 20; i++) {
	
		mesh_[i]->SetTextureManager(textureManager2);

	}
	sprite->SetTextureManager(textureManager3);
	sprite->Initialize();

	sprite2->SetTextureManager(textureManager4);
	sprite2->Initialize();

	model->SetTextureManager(textureManager3);
	model2->SetTextureManager(textureManager4);
	

	sphere->SetMesh(mesh_[0]); 
	sphere->SetTextureManager(textureManager3);
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
			//camera->Update();
			/*sprite->Update();
			sprite2->Update();*/
			
			if (Reset) {
				transform.rotate.y += 0.03f;
				//transform.translate.z += 0.03f;
			}
			/*for (int i = 0; i < 20; i++) {
				*mesh_[i]->wvpData = camera->worldViewProjectionMatrix;
				mesh_[i]->Update( color[i]);
			
				mesh_[i]->Draw();

			}*/
			
			if (input->PushKey(DIK_1)) {
				num++;
			}

			if (input->PushKey(DIK_2)) {
				num--;
			}
			//*model->wvpData = camera->worldViewProjectionMatrix;
			//model->Draw(transform);

			//*model2->wvpData = camera->worldViewProjectionMatrix;
			//model2->Draw(transformA);

			if (useMonsterBall) {
				sphere->SetTextureManager(textureManager3);
			} 
			else{
				sphere->SetTextureManager(textureManager3);
			}
			sphere->Draw(transform);
			//sprite->Draw();
			//sprite2->Draw();
			

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

			ImGui::DragFloat3("spriteT : ", &sprite->transform_.translate.x, 0.1f);

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
	sWinApp->Release();

	for (int i = 0; i < 20; i++) {
		mesh_[i]->Release();
	}
	imGuiCommon->Release();
	textureManager->Release();
	textureManager2->Release();
	textureManager3->Release();
	textureManager4->Release();

	sprite->Release();
	sprite2->Release();
	sphere->Release();
	model->Release();
	model2->Release();
	sDirctX->Release();
	
	CoUninitialize();
	return 0;
}