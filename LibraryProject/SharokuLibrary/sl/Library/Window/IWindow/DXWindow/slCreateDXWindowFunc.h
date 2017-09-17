//==================================================================================================================================//
//!< @file		slCreateDXWindowFunc.h
//!< @brief		DXWinodwクラスを生成する関数のヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/06	更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_CREATE_DXWINDOW_FUNC_H
#define SL_CREATE_DXWINDOW_FUNC_H

#include <windows.h>
#include "../../../Utility/slTypes.h"
#include "../../../SmartPointer/UniquePtr/slUniquePtr.h"

namespace sl
{

class DXWindow;

/* 
* DXWindowクラスを生成する関数
* @param[in] pWinName	ウィンドウネーム
* @param[in] winWidth	ウィンドウの横幅
* @param[in] winHeight	ウィンドウの縦幅
* @param[in] hIcon		アイコン 
* @param[in] hWndParent 親ハンドル
* @return DXWindowクラスのインスタンスへのポインタ
*/
UniquePtr<DXWindow> CreateDXWindow(t_char* pWinName, int winWidth, int winHeight, HICON  hIcon, HWND hWndParent);

}	// namespace sl

#endif	// SL_CREATE_DXWINDOW_FUNC_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
