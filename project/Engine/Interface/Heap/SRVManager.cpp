#include "SRVManager.h"
#include "DirectXCommon.h"

const uint32_t SRVManager::kMaXSRVCount = 512;

void SRVManager::Init() {
	// デスクリプタヒープの生成
	descriptorHeap_ = DirectXCommon::GetInstance()->CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kMaXSRVCount, true);
	// デスクリプタ1個分のサイズを取得して記録
	descriptorSize_ = DirectXCommon::GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

uint32_t SRVManager::Allocate()
{
	// return する番号をいったん記録しておく
	int index = useIndex_;
	// 次回のために番号を1進める
	useIndex_++;
	// 上で記録した番号をreturn
	return index;
}

SRVManager* SRVManager::GetInstance()
{
	static SRVManager instance;
	return &instance;
}

D3D12_CPU_DESCRIPTOR_HANDLE SRVManager::GetCPUDescriptorHandle(uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize_ * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE SRVManager::GetGPUDescriptorHandle(uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize_ * index);
	return handleGPU;
}

void SRVManager::CreateSRVforTexture2D(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT Format, UINT MipLevels)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(pResource, &srvDesc, GetCPUDescriptorHandle(srvIndex));

}

void SRVManager::CreateSRVforStructuredBuffer(uint32_t srvIndex, ID3D12Resource* pResource, UINT numElements, UINT structureByteStride)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	DirectXCommon::GetInstance()->GetDevice()->CreateShaderResourceView(pResource, &srvDesc, GetCPUDescriptorHandle(srvIndex));
}

void SRVManager::PreDraw()
{
	// 描画用のDescriptorHeapの設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { descriptorHeap_.Get() };
	DirectXCommon::GetInstance()->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);
}

void SRVManager::SetGraphicsRootDescriptortable(UINT rootParameterIndex, uint32_t srvIndex)
{
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootDescriptorTable(rootParameterIndex, GetGPUDescriptorHandle(srvIndex));
}
