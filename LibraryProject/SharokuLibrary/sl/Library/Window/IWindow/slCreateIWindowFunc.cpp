//==================================================================================================================================//
//!< @file		slCreateIWindowFunc.cpp
//!< @brief		ウィンドウを生成する関数の実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/05	更新履歴：2017/09/23
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

UniquePtr<IWindow> CreateMainWindow(const WindowCreationData& rData)
{
	HICON	    hIcon = LoadIcon(NULL, IDI_APPLICATION);
	return CreateDXWindow(rData, hIcon, NULL);
}

UniquePtr<IWindow> CreateMainWindow(const WindowCreationData& rData, unsigned short iconID)
{
	HICON	    hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(iconID));
	return CreateDXWindow(rData, hIcon, NULL);
}

UniquePtr<IWindow> CreateSubWindow(const WindowCreationData& rData, const WindowHandle& rMainWinHandle)
{
	HICON	    hIcon = LoadIcon(NULL, IDI_APPLICATION);
	HWND parentHandle  = static_cast<HWND>(rMainWinHandle.m_pAdress);

	return CreateDXWindow(rData, hIcon, parentHandle);
}	

#endif // DIRECT_X_11

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
