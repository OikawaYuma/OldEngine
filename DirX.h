#pragma once
#include <Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include"function.h"
#include<string>
#include<format>

#include"WinApp.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
class DirX
{
public:
	DirX(HWND hwnd);
	~DirX();

	void DirXUpdata();

	IDXGIFactory7* dxgiFactory;
	HRESULT hr;

	//アダプター
	IDXGIAdapter4* useAdapter;
	ID3D12Device* device;
	ID3D12CommandQueue* commandQueue;
	ID3D12CommandAllocator* commandAllocator;
	ID3D12GraphicsCommandList* commandList;

	//スワップチェーン
	IDXGISwapChain4* swapChain;
	ID3D12DescriptorHeap* rtvDescriptorHeap;
	ID3D12Resource* swaoChainResources[2] = { nullptr };

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
};

