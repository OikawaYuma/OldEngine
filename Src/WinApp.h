#pragma once
#include<Windows.h>
#include<cstdint>

#include<d3d12.h>
#include<dxgi1_6.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


class WinApp final
{

private:
	
public:
	/*-----Default Method-----*/
	// 初期化
	void Initialize(const wchar_t* label);
	// 解放処理
	void Release();

	/*-----User Method-----*/

	// シングルトンパターンの実装
	// コピーコンストラクタを無効にする
	WinApp(const WinApp& obj) = delete;
	// 代入演算子を無効にする
	WinApp& operator=(const WinApp& obj) = delete;

	// Accessor
	static WinApp* GetInstance();

	static int32_t GetKClientWidth() { return kClientWidth_; };
	static int32_t GetKClientHeight() { return kClientHeight_; };

	static HWND GetHwnd() { return hwnd_; }


	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


	

private:
	// コンストラクタ
	WinApp() = default;
	//デストラクタ
	~WinApp() = default;

	// ウィンドウの生成
	static HWND hwnd_;

	//ウィンドウクラス
	WNDCLASS wc_{};

	// クライアント領域のサイズ
	const static  int32_t kClientWidth_ = 1280;
	const static  int32_t kClientHeight_ = 720;

	static ID3D12Debug1* debugController_;
	

};




