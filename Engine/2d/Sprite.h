#pragma once
#include "PSO.h"

#include <DirectXTex.h>
#include <string>
#include <string>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dxcapi.h>

#include "function.h"
#include <wrl.h>
#include "Transform.h"
#include "VertexData.h"
#include "Vector4.h"
#include"Vector3.h"
#include"Vector2.h"
#include "Matrix4x4.h"
#include "Material.h"
#include "DirectionLight.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
class WinAPI;
class DirectXCommon;
class Camera;
class Mesh;
class TextureManager;
class Sprite
{
public:
	Sprite();
	~Sprite();

	void Initialize();
	//void Update();
	void Draw(uint32_t texture);
	void Release();
	void SetTextureManager(TextureManager* textureManager) {
		textureManager_ = textureManager;
	}

	Transform GetTransform() {
		return transform_;
	}
	Transform transform_;
	D3D12_VERTEX_BUFFER_VIEW CreateBufferView();
private:
	PSO* pso_ = nullptr;
	Microsoft::WRL::ComPtr < ID3D12Resource> vertexResourceSprite_ =nullptr;
	WinAPI* sWinAPI;
	DirectXCommon* sDirectXCommon;
	Mesh* mesh_;
	TextureManager* textureManager_ = nullptr;
	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite_{};

	VertexData* vertexDataSprite_ = nullptr;

	// Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	Microsoft::WRL::ComPtr < ID3D12Resource> transformationMatrixResouceSprite;
	// データを書き込む
	Matrix4x4* transformationMatrixDataSprite = nullptr;

	Transform transformSprite_;
	
	//D3D12_DESCRIPTOR_RANGE descriptorRange_[1] = {};

	// RootParmeter作成。複数でっていできるので配列。今回は結果１つだけなので長さ1の配列
	//D3D12_ROOT_PARAMETER rootParamerters[1] = {};
	
	uint32_t* indexDataSprite;
	Microsoft::WRL::ComPtr < ID3D12Resource> indexResourceSprite;
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};


	// 実際に頂点リソースを作る
	Microsoft::WRL::ComPtr <ID3D12Resource> materialResource;
	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};
	// 頂点リソースにデータを書き込む
	Material* materialData;


	// 平行光源用
	Microsoft::WRL::ComPtr < ID3D12Resource> directionalLightResource;
	// データを書き込む
	DirectionalLight* directionalLightData;
	Transform transformUv;

};

