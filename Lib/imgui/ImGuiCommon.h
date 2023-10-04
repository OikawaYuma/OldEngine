#pragma once
#include"imgui.h"
#include"imgui_impl_win32.h"
#include"imgui_impl_dx12.h"

class WinApp;
class DirectXCommon;
class ImGuiCommon
{
public:
	
	void Initialize();
	void Update();
	void Draw();

	void UIParameter();
	void UICreate();
	void Release();

private:

	WinApp* sWinApp_ = nullptr;
	DirectXCommon* sDirectXCommon_ = nullptr;
};

