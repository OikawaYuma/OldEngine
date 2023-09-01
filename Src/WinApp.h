#pragma once
#include<Windows.h>
#include<cstdint>

#include<d3d12.h>
#include<dxgi1_6.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


class WinApp
{

private:
	
public:
	WinApp();
	~WinApp();
	static WinApp* GetInstance();
	
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	/*WinApp();
	~WinApp();*/
	void Initialize(const wchar_t* label);
	void Release();

	WNDCLASS wc{};

 static HWND hwnd_;

	// クライアント領域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	ID3D12Debug1* debugController;
	
	

};




