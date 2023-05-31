#pragma once
#include<Windows.h>
#include<cstdint>

class WinApp
{
public:
	
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	WinApp(const wchar_t* label);
	~WinApp();

	WNDCLASS wc{};

 static HWND hwnd_;

	// クライアント領域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;
	

};




