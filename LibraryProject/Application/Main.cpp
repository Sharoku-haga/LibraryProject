﻿//==================================================================================================================================//
//!< @file		Main.cpp
//!< @brief		Library用テストアプリケーション
//!< @author	T.Haga
//!< @data		作成日時：2017/09/07
//==================================================================================================================================//

#include <crtdbg.h>
#include "sl/Library/EntryPoint/slEntryPoint.h"

/* Entry Point ---------------------------------------------------------------------------------------- */

ENTRY_FUNCTION()
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
