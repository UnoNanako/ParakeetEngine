#include <Windows.h>
#include <memory>
#include "MyGame.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd) {
	std::unique_ptr<MyGame> game = std::make_unique<MyGame>();
	game->Run();
	return 0;
}