#pragma once
#include <Windows.h>
#include <cstdint>

class WinApp {
public: //メンバ関数
	
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return wc.hInstance; }

public:
	//定数　クライアント領域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

private:
	//ウィンドウハンドル
	HWND hwnd = nullptr;
	WNDCLASS wc{};
};

