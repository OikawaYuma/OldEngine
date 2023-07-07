#pragma once
#include"imgui.h"
#include"imgui_impl_win32.h"
#include"imgui_impl_dx12.h"

class WinApp;
class DirX;
class ImGuiCommon
{
public:
	
	void Initialize(WinApp* winApp_, DirX* dirX_);
	void Update();
	void Draw(DirX* dirX_);

	void UIParameter();
	void UICreate(DirX* dirX);

};

