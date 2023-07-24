#pragma once
#include"imgui.h"
#include"imgui_impl_win32.h"
#include"imgui_impl_dx12.h"

class WinApp;
class DirXCommon;
class ImGuiCommon
{
public:
	
	void Initialize(WinApp* winApp_, DirXCommon* dirX_);
	void Update();
	void Draw(DirXCommon* dirX_);

	void UIParameter();
	void UICreate(DirXCommon* dirX);
	void Release();
};

