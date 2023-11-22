#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
class WinAPI;
class Input
{
public:
	Input();
	~Input();

	void Initialize();
	void Update();
	void Draw();
	void Release();

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool PushKey(BYTE keyNumber);

private:

	
	BYTE keys[256] = {};
	// DirectInputの初期化
	IDirectInput8* directInput = nullptr;
	HRESULT result;

	// キーボードデバイスの生成
	IDirectInputDevice8* keyboard = nullptr;

	WinAPI* sWinAPI = nullptr;
};

