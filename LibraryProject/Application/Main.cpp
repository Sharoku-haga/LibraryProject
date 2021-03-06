﻿//==================================================================================================================================//
//!< @file		Main.cpp
//!< @brief		Library用テストアプリケーション
//!< @author	T.Haga
//!< @data		作成日時：2017/09/07	更新履歴：2017/09/22
//==================================================================================================================================//

#include <crtdbg.h>
#include "sl/Library/Debugger/slDebug.h"
#include "sl/Library/EntryPoint/slEntryPoint.h"

/* Entry Point ---------------------------------------------------------------------------------------- */

ENTRY_FUNCTION()
{
	sl::CheckMemoryLeak();
	return 0;
}

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
