//==================================================================================================================================//
//!< @file		Main.cpp
//!< @brief		Library用テストプログラム
//!< @author	T.Haga
//==================================================================================================================================//

/** @todo このソースはもう少しLibraryができてからきれいにする */

#include <windows.h>
#include <crtdbg.h>
#include "sl/sl.h"
#include "App\App.h"

#define TITLE "テスト"
#define WIN_WIDTH	1200
#define WIN_HEIGHT	900

/* Entry Point ---------------------------------------------------------------------------------------- */

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sl::IWindow*	pWindow = nullptr;
	pWindow = new sl::dx11::Window();

	if(!pWindow->Initialize(TITLE, WIN_WIDTH, WIN_HEIGHT))
	{
		// 作成失敗
		return 0;
	}
	
	sl::dx11::GraphicsDevice* pGraphicsDevice = nullptr;
	pGraphicsDevice = new sl::dx11::GraphicsDevice();
	if(!pGraphicsDevice->Initialize(pWindow->GetHwnd()))
	{
		// 作成失敗
	}

	
	/* アプリケーションの初期化 ----------------------------------------------------------------------------------------------- */

	app::App* pApp = new app::App();
	pApp->Initialize(pGraphicsDevice);

	while(true)
	{
		if(pWindow->Update())
		{
			break;
		}
		else
		{
			if(pApp->Update())
			{
				break;
			}
		}
	}

	delete pApp;
	delete pGraphicsDevice;
	delete pWindow;
	return 0;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
