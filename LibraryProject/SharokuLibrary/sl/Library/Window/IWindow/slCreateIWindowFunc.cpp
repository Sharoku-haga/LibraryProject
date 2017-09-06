//==================================================================================================================================//
//!< @file		slCreateIWindowFunc.cpp
//!< @brief		ウィンドウを生成する関数の実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/05
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <windows.h>
#include "../../../slBuild.h"
#include "../IWindow/DXWindow/slDXWindow.h"
#include "DXWindow/slCreateDXWindowFunc.h"
#include "slIWindow.h"
#include "slCreateIWindowFunc.h"

namespace sl
{

/* Functions -------------------------------------------------------------------------------------------------- */

#ifdef DIRECT_X_11

UniquePtr<IWindow> CreateMainWindow(t_char* pWinName, int winWidth, int winHeight)
{
	HICON	    hIcon = LoadIcon(NULL, IDI_APPLICATION);
	return CreateDXWindow(pWinName, winWidth, winHeight, hIcon, NULL);
}

UniquePtr<IWindow> CreateMainWindow(t_char* pWinName, int winWidth, int winHeight, unsigned short iconID)
{
	HICON	    hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(iconID));
	return CreateDXWindow(pWinName, winWidth, winHeight, hIcon, NULL);
}

UniquePtr<IWindow> CreateSubWindow(t_char* pWinName, int winWidth, int winHeight, const WindowHandle& rMainWinHandle)
{
	HICON	    hIcon = LoadIcon(NULL, IDI_APPLICATION);
	HWND parentHandle  = static_cast<HWND>(rMainWinHandle.m_pAdress);

	return CreateDXWindow(pWinName, winWidth, winHeight, hIcon, parentHandle);
}	

#endif // DIRECT_X_11

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
