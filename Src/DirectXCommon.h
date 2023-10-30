#pragma once
#include <Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include"function.h"
#include<string>
#include<format>
#include <wrl.h>

#include"WinApp.h"
#include<dxcapi.h>
#include"TextureManager.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")
/*----------------------------------------------------------
   このクラスはシングルトンパターンのを元に設計する
--------------------------------------------------------------*/
class Mesh;
class WinApp;
class ImGuiCommon;
class TextureManager;

class DirectXCommon final{
public:
	static DirectXCommon* GetInstance();

	DirectXCommon() = default;
	~DirectXCommon() = default;

	void Initialize();
	void BeginFrame();
	void ViewChange();
	void Release();

	ID3D12DescriptorHeap* CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors,bool shaderVisible);
	ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);
	// Accessor
	ID3D12Device* GetDevice() { return device_.Get(); };
	IDxcUtils* GetDxcUtils() { return dxcUtils_; };
	IDxcCompiler3* GetDxcCompiler() { return dxcCompiler_; };
	IDxcIncludeHandler* GetIncludeHandler() { return includeHandler_; };
	ID3D12GraphicsCommandList* GetCommandList() { return commandList_.Get(); };
	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc() { return swapChainDesc_; };
	ID3D12DescriptorHeap* GetSrvDescriptorHeap() { return srvDescriptorHeap_.Get(); };
	D3D12_RENDER_TARGET_VIEW_DESC GetrtvDesc() { return rtvDesc_; };
	D3D12_DEPTH_STENCIL_DESC GetDepthStencilDesc() { return depthStencilDesc_; };

	/*D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index) {
		D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		handleCPU.ptr += (descriptorSize * index);
		return handleCPU;
	}

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index) {
		D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		handleGPU.ptr += (descriptorSize * index);
		return handleGPU;
	}*/

private:
	// DXGIファクトリーの生成
	Microsoft::WRL::ComPtr < IDXGIFactory7> dxgiFactory;
	// HRESULTはWindows系のエラーコードであり、
	// 関数が成功したかどうかをSUCCEEDEDマクロで判定できる
	HRESULT hr_;
	
	// 使用するアダプタ用の変数
	Microsoft::WRL::ComPtr < IDXGIAdapter4> useAdapter_;
	Microsoft::WRL::ComPtr < ID3D12Device> device_;
	Microsoft::WRL::ComPtr < ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr < ID3D12CommandAllocator> commandAllocator_;
	Microsoft::WRL::ComPtr < ID3D12GraphicsCommandList> commandList_;

	//スワップチェーン
	Microsoft::WRL::ComPtr < IDXGISwapChain4> swapChain_;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};

	// ディスクリプタヒープの生成
	Microsoft::WRL::ComPtr < ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;
	Microsoft::WRL::ComPtr < ID3D12DescriptorHeap> srvDescriptorHeap_ = nullptr;
	Microsoft::WRL::ComPtr < ID3D12Resource> swapChainResources_[2] = {nullptr};

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};
	// ディスクリプタヒープの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle_;
	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];

	// これから書き込むバックバッファのインデックスを取得
	UINT backBufferIndex_;
	// TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier_{};

	// 初期値0でFenceを作る
	Microsoft::WRL::ComPtr < ID3D12Fence> fence_;
	uint64_t fenceValue_;
	HANDLE fenceEvent_;

	// dxCompilerを初期化
	IDxcUtils* dxcUtils_;
	IDxcCompiler3* dxcCompiler_;

	IDxcIncludeHandler* includeHandler_;
	WinApp* sWinApp_ = nullptr;
	TextureManager* textureManager_ = nullptr;


	// DepthStencilTextureをウィンドウのサイズで作成
	Microsoft::WRL::ComPtr < ID3D12Resource> depthStencilResource_;

	// DSVようのヒープでディスクリプタの数は1。DSVはShader内で触るものではないので、ShaderVisibleはfalse
	Microsoft::WRL::ComPtr < ID3D12DescriptorHeap> dsvDescriptorHeap_;
	// DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc_{};

	// 描画先のRTVを設定する
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;
};

