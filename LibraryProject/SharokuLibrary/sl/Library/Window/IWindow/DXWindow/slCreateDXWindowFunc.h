//==================================================================================================================================//
//!< @file		slCreateDXWindowFunc.h
//!< @brief		DXWinodwクラスを生成する関数のヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/06	更新履歴：2017/09/23
//==================================================================================================================================//

#ifndef SL_CREATE_DXWINDOW_FUNC_H
#define SL_CREATE_DXWINDOW_FUNC_H

#include <windows.h>
#include "../../../SmartPointer/UniquePtr/slUniquePtr.h"

namespace sl
{

class DXWindow;
struct WindowCreationData;

/* 
* DXWindowクラスを生成する関数
* @param[in] rData		ウィンドウ作成時の設定データ
* @param[in] hWndParent 親ハンドル
* @return DXWindowクラスのインスタンスへのポインタ
*/
UniquePtr<DXWindow> CreateDXWindow(const WindowCreationData& rData, HICON  hIcon, HWND hWndParent);

}	// namespace sl

#endif	// SL_CREATE_DXWINDOW_FUNC_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
