#pragma once
#include <cstdint>
#include <wrl.h>
#include <d3d12.h>
/*----------------------------------------------------------
   このクラスはシングルトンパターンを元に設計する
--------------------------------------------------------------*/

class SRVManager
{
public:
	void Init();

	uint32_t Allocate();
private:
	SRVManager() = default;
	~SRVManager() = default;
	const SRVManager& operator=(const SRVManager&) = delete;
public:
	static SRVManager* GetInstance();

	// 最大SRV数（最大テクスチャ枚数）
	static const uint32_t kMaXSRVCount;
	// SRV用のデスクリプタサイズ
	uint32_t descriptorSize_;
	// SRV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_;
	// 次に使用するSRVインデックス
	uint32_t useIndex_ = 0;

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);

	// SRV生成（テクスチャ用）
	void CreateSRVforTexture2D(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT Format, UINT MipLevels);
	// SRV生成（Structured Buffer用）
	void CreateSRVforStructuredBuffer(uint32_t srvIndex, ID3D12Resource* pResource, UINT numElements, UINT structureByteStride);

	void PreDraw();

	void SetGraphicsRootDescriptortable(UINT rootParameterIndex, uint32_t srvIndex);


};

