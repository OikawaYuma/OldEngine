#pragma once
#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include <dxcapi.h>

//#include"DirectXCommon.h"
#include "VertexData.h"
#include "Vector4.h"
#include"Vector3.h"
#include"Vector2.h"
#include"Matrix4x4.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")

class DirectXCommon;
class WinApp;
class TextureManager;
class Mesh;
class Sphere
{
public :
	Sphere();
	~Sphere();
	void Initialize();
	void Update();
	void Draw();
	void Release();
	
	void SetMesh(Mesh* mesh) {
		mesh_ = mesh;
	}
	void SetTextureManager(TextureManager* textureManager) {
		textureManager_ = textureManager;
	}
	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportmatrix, int color);

	D3D12_VERTEX_BUFFER_VIEW  CreateBufferView();
private:
	
	WinApp* sWinApp = nullptr;
	DirectXCommon* sDirectXCommon_ = nullptr;
	Mesh* mesh_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	// RootSignature作成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	// シリアライズしてバイナリにする
	ID3DBlob* signatureBlob;
	ID3DBlob* errorBlob;
	// バイナリを元に生成
	ID3D12RootSignature* rootSignature;
	// InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	D3D12_INPUT_LAYOUT_DESC  inputLayoutDesc{};
	// blendStateの設定
	D3D12_BLEND_DESC blendDesc{};
	// RasiterzerStateの設定
	D3D12_RASTERIZER_DESC rasterizerDesc{};

	

	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	//実際に生成
	ID3D12PipelineState* graphicsPipelineState;
	// RootParmeter作成。複数でっていできるので配列。今回は結果１つだけなので長さ1の配列
	D3D12_ROOT_PARAMETER rootParamerters[3] = {};

	/*頂点用*/
	// 実際に頂点リソースを作る
	ID3D12Resource* vertexResource;
	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// 頂点リソースにデータを書き込む
	VertexData* vertexData_;


	/*色用*/
	//頂点リソースの設定
	// 実際に頂点リソースを作る
	ID3D12Resource* materialResource;
	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};
	// 頂点リソースにデータを書き込む
	Vector4* materialData;

	/*移動用*/
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	ID3D12Resource* wvpResource;
	// データを書き込む
	Matrix4x4* wvpData;

	// 頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW wvpBufferView{};
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	D3D12_DESCRIPTOR_RANGE descriptorRange_[1] = {};
	//ビューポート
	D3D12_VIEWPORT viewport{};
	// シザー矩形
	D3D12_RECT scissorRect{};








	


};

