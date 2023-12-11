#include "Input.h"
#include "WinAPI.h"

void Input::Initialize() {
	WinAPI *sWinAPI = WinAPI::GetInstance();
	// DirectInputの初期化
	ComPtr<IDirectInput8> directInput = nullptr;
	result = DirectInput8Create(
		sWinAPI->GetWc().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));
	
	// キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(
		sWinAPI->GetHwnd(),DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::Update() {
	// 前回のキー入力を保存
	memcpy(preKeys, keys, sizeof(keys));

	// キーボード情報の取得開始
	keyboard->Acquire();

	keyboard->GetDeviceState(sizeof(keys), keys);
}

bool Input::PushKey(BYTE keyNumber)
{
	if (keys[keyNumber]) {
		return true;
	}
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (keys[keyNumber] && preKeys[keyNumber] == 0) {
		return true;
	}
	return false;
}
Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}


