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
	game->Initialize();

	MSG msg{};
	while (msg.message != WM_QUIT) {
		//Windoeにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			///--------------------更新処理ここから--------------------
			game->Update();
			///--------------------更新処理ここまで--------------------
			game->Draw();
		}
	}

	game->Finalize();
	return 0;
}