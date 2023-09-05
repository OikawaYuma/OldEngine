#include "ImGuiCommon.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "imgui.h"
#include "imgui_impl_dx12.h"
#include "imgui_impl_win32.h"


//void ImGuiCommon::Initialize(WinApp* winApp_, DirectXCommon* dirX_) {
//	//ImGuiの初期化。詳細はさして重要ではないので省略する。
//	//こういうもんである
//	IMGUI_CHECKVERSION();
//	ImGui::CreateContext();
//	ImGui::StyleColorsDark();
//	ImGui_ImplWin32_Init(winApp_->GetHwnd());
//	ImGui_ImplDX12_Init(dirX_->device,
//		dirX_->swapChainDesc.BufferCount,
//		dirX_->rtvDesc.Format,
//		dirX_->srvDescriptorHeap,
//		dirX_->srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
//		dirX_->srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
//
//}
//
//void ImGuiCommon::Update() {
//	ImGui_ImplDX12_NewFrame();
//	ImGui_ImplWin32_NewFrame();
//	ImGui::NewFrame();
//
//	ImGui::ShowDemoWindow();
//};
//
//void ImGuiCommon::Draw(DirectXCommon* dirX_) {
//	ImGui::Render();
//	//描画用のDescriptorの設定
//	ID3D12DescriptorHeap* descriptorHeaps[] = { dirX_->srvDescriptorHeap };
//	dirX_->commandList->SetDescriptorHeaps(1, descriptorHeaps);
//	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dirX_->commandList);
//}
//
//
//void ImGuiCommon::UICreate(DirectXCommon* dirX) {
//	// 実際のcoomandListのImguiの描画コマンドを積む
//	//ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dirX->commandList);
//}
//
//
//void ImGuiCommon::Release() {
//	ImGui_ImplDX12_Shutdown();
//	ImGui_ImplWin32_Shutdown();
//	ImGui::DestroyContext();
//}