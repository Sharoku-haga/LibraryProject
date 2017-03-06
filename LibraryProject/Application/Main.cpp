//==================================================================================================================================//
//!< @file		Main.cpp
//!< @brief		Library用テストプログラム
//!< @author	T.Haga
//==================================================================================================================================//

/** @todo このソースはもう少しLibraryができてからきれいにする */

#include <windows.h>
#include "sl/sl.h"

#define TITLE "テスト"
#define WIN_WIDTH	1200
#define WIN_HEIGHT	900

/* Entry Point ---------------------------------------------------------------------------------------- */

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	sl::IWindow*	pWindow = nullptr;
	pWindow = new sl::dx11::Window();

	if(!pWindow->Initalize(TITLE, WIN_WIDTH, WIN_HEIGHT))
	{
		// 作成失敗
	}
	
	sl::dx11::GraphicsDevice* pGraphicsDevice = nullptr;
	pGraphicsDevice = new sl::dx11::GraphicsDevice();

	if(!pGraphicsDevice->Initialize(pWindow->GetHwnd()))
	{
		// 作成失敗
	}

	while(true)
	{
		if(pWindow->Update())
		{
			break;
		}
		else
		{

		}
	}

	delete pGraphicsDevice;
	delete pWindow;
	return 0;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
