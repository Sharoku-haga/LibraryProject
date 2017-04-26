//==================================================================================================================================//
//!< @file		Main.cpp
//!< @brief		Library用テストプログラム
//!< @author	T.Haga
//==================================================================================================================================//

/** @todo このソースはもう少しLibraryができてからきれいにする */

#include <windows.h>
#include <crtdbg.h>
#include "../SharokuLibrary/sl/slISharokuLibrary.h"
#include "App\App.h"

#define TITLE "テスト"
#define WIN_WIDTH	1200
#define WIN_HEIGHT	900

/* Entry Point ---------------------------------------------------------------------------------------- */

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sl::ISharokuLibrary::Create();
	sl::ISharokuLibrary* pLibrary = sl::ISharokuLibrary::Instance();
	pLibrary->Initialize(TITLE, WIN_WIDTH, WIN_HEIGHT);

	while(true)
	{
		if(pLibrary->UpdateWindow())
		{
			break;
		}
		else
		{
		}
	}

	sl::ISharokuLibrary::Delete();
	return 0;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
