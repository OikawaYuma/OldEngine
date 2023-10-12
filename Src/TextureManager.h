#pragma once
#include <DirectXTex.h>
#include <string>
#include <string>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dxcapi.h>

#include "function.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
class DirectXCommon;
class WinApp;
class TextureManager
{
public:
	
	void Initialize(const std::string& filePath,int num);
	void Update();
	void Release();
	void SetTexture();
	void SetDirectXCommon();


	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	// テクスチャファイルを呼んでプログラムを使えるようにする
	DirectX::ScratchImage image_{};
	std::wstring filePathW_; 
	
	// エラー検知用変数
	HRESULT hr_;

	// Textureを読んで転送する
	DirectX::ScratchImage mipImages_;

	// 利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties_{};


	// Resourceの生成
	ID3D12Resource* resource_;
	ID3D12Resource* textureResource_;

	

	// metaDataを基にSRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc_{};

	// DirectX12のTextureResourceを作る
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& matdata);


	
	D3D12_RESOURCE_DESC resourceDesc_{};
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;

	
	D3D12_DESCRIPTOR_RANGE descriptorRange_[1] = {};

	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	
private:
	DirectXCommon* sDirectXCommon_ = nullptr;
	WinApp* sWinApp_ = nullptr;

};

