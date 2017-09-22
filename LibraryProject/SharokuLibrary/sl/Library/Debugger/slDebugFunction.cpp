//==================================================================================================================================//
//!< @file		slDebugFunction.cpp
//!< @brief		デバック用の関数群の実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/22	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDebugFunction.h"
#include <crtdbg.h>

namespace sl
{

#ifdef _DEBUG

#include <windows.h>
#include <stdio.h>

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

constexpr	int OutputLogStrMax = 512;			// ログの文字の最大数

}

/* Global Functions ------------------------------------------------------------------------------------------- */

void CheckMemoryLeak()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void slOutputDebugString(t_char* pStr, ...)
{
	t_char outputString[OutputLogStrMax];
	
	va_list args;
	va_start(args, pStr);

	vsprintf_s(outputString, sizeof(outputString), pStr, args);

	OutputDebugString(outputString);

	va_end(args);

	OutputDebugString("\n");
}

#else

void CheckMemoryLeak() {}

void slOutputDebugString(t_char* pStr, ...) {}

#endif

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
