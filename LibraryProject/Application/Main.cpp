//==================================================================================================================================//
//!< @file		Main.cpp
//!< @brief		Library用テストプログラム
//!< @author	T.Haga
//==================================================================================================================================//

#include <windows.h>
#include <crtdbg.h>
#include "App/App.h"
#include "sl/Library/Singleton/slBasicSingleton.h"

/* Entry Point ---------------------------------------------------------------------------------------- */

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//app::App* pApp = new app::App();
	//pApp->Initialize();
	//pApp->Update();
	//delete pApp;
	return 0;
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
