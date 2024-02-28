#pragma once
#include <DirectXTex.h>
#include <string>
#include <string>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dxcapi.h>
#include <wrl.h>
#include "function.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
/*----------------------------------------------------------
   このクラスはシングルトンパターンのを元に設計する
--------------------------------------------------------------*/
class TextureManager
{
private:
	TextureManager() = default;
	~TextureManager() = default;
	const TextureManager& operator=(const TextureManager&) = delete;
public:
	static TextureManager* GetInstance();
	static int PlusIndex();
	// 格納しその保管番号を返す
	static int StoreTexture(const std::string& filePath);
	void Release();

	// メタデータを取得
	const DirectX::TexMetadata& GetMetaData(uint32_t textureIndex);
	static DirectX::ScratchImage LoadTexture(const std::string& filePath);

	// DirectX12のTextureResourceを作る
	static Microsoft::WRL::ComPtr <ID3D12Resource> CreateTextureResource(Microsoft::WRL::ComPtr <ID3D12Device> device, const DirectX::TexMetadata& matdata);

	static void UploadTextureData(Microsoft::WRL::ComPtr <ID3D12Resource>, const DirectX::ScratchImage& mipImages);

	// Getter
	D3D12_CPU_DESCRIPTOR_HANDLE GetTextureSrvHandleCPU_(uint32_t texture){return textureSrvHandleCPU_[texture];}
	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU_(uint32_t texture) { return textureSrvHandleGPU_[texture] ; }

	int GetIndex() { return index_; }
private:
	// デスクリプタ―の数
	static const size_t kNumDescriptors = 256;
	
	// エラー検知用変数
	HRESULT hr_;

	// 現在空白のHeap位置を表す
	static int index_ ;
	//SRV
	const static uint32_t SRVSizes = 128;
	// metaDataを基にSRVの設定
	
	// Resourceの生成
	static Microsoft::WRL::ComPtr <ID3D12Resource> textureResource_[SRVSizes];
	static D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_[SRVSizes];
	static D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_[SRVSizes];
	static DirectX::TexMetadata metadata_[SRVSizes];
	static D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_[SRVSizes];
	//D3D12_DESCRIPTOR_RANGE descriptorRange_[1] = {};
};

