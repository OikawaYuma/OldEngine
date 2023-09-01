#pragma once
#include <Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include"function.h"
#include<string>
#include<format>

//#include"WinApp.h"
#include<dxcapi.h>
//#include"TextureManager.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
class Mesh;
class WinApp;
class ImGuiCommon;
class DirectXCommon final{

private:
	
public:
	static DirectXCommon* GetInstance();
	DirectXCommon();
	~DirectXCommon();
	/*DirectXCommon();
	~DirectXCommon();*/
	void Initialize();
	void BeginFrame();
	void ViewChange();
	void Release();

	ID3D12DescriptorHeap* CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors,bool shaderVisible);

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
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	ID3D12DescriptorHeap* srvDescriptorHeap = nullptr;
	ID3D12Resource* swapChainResources[2] = { nullptr };

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	// ディスクリプタヒープの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;
	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];

	// これから書き込むバックバッファのインデックスを取得
	UINT backBufferIndex;
	// TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};

	// 初期値0でFenceを作る
	ID3D12Fence* fence;
	uint64_t fenceValue;
	HANDLE fenceEvent;

	// dxCompilerを初期化
	IDxcUtils* dxcUtils;
	IDxcCompiler3* dxcCompiler;

	IDxcIncludeHandler* includeHandler = nullptr;






	
};

