#pragma once
#include<Windows.h>
#include<string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
std::wstring ConvertString(const std::string& str);
std::string ConvertString(const std::wstring& str);

