#pragma once
#include "PSOModel.h"
#include "ModelData.h"
#include "MaterialData.h"
#include "vertexData.h"

#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include <dxcapi.h>
#include <fstream>
#include <sstream>
#include <cassert>
#include <Material.h>
#include <Transform.h>
#include <Camera.h>
#include <WorldTransform.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
class Object3d
{
public:
	void Init(const std::string& directoryPath, const std::string& filename, const Material& material);
	void Update();
	void Draw(WorldTransform worldTransform, uint32_t texture, Camera* camera, const Material& material, const DirectionalLight& dire);
	void Release();

	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
private:
	HRESULT hr;
	// RootSignature作成

	DirectXCommon* directXCommon_;
	WinAPI* sWinAPI_;
	TextureManager* textureManager_ = nullptr;
	PSO* pso_ = nullptr;

	TransformationMatrix* wvpData;
	/*移動用*/
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	Microsoft::WRL::ComPtr < ID3D12Resource> wvpResource;
	// データを書き込む

	// 平行光源用
	Microsoft::WRL::ComPtr < ID3D12Resource> directionalLightResource;
	// データを書き込む
	DirectionalLight* directionalLightData;

	//カメラ用
	Microsoft::WRL::ComPtr < ID3D12Resource> cameraForGPUResource_;
	CameraForGPU* cameraForGPUData_;

	Transform transformUv;
	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW wvpBufferView{};
	Camera* camera_ = nullptr;

};

