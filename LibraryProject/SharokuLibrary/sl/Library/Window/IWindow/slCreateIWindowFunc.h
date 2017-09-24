//==================================================================================================================================//
//!< @file		slCreateIWindowFunc.h
//!< @brief		ウィンドウを生成する関数のヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/05	更新履歴：2017/09/23
//==================================================================================================================================//

#ifndef SL_CREATE_IWINDOW_FUNC_H
#define SL_CREATE_IWINDOW_FUNC_H

#include "../../Utility/slDefine.h"
#include "../slWindowDeclaration.h"
#include "../../SmartPointer/UniquePtr/slUniquePtr.h"


namespace sl
{

interface IWindow;

/**
* メインウィンドウを作成する関数
* 通常時に使用する
* @param[in] rData		ウィンドウ作成時の設定データ
* @return IWindowクラスのインスタンスのポインタ
*/
UniquePtr<IWindow> CreateMainWindow(const WindowCreationData& rData);

/**
* メインウィンドウを作成する関数
* アイコンも作成するときに使用する
* @param[in] rData		ウィンドウ作成時の設定データ
* @param[in] iconID		アイコンID
* @return IWindowクラスのインスタンスのポインタ
*/
UniquePtr<IWindow> CreateMainWindow(const WindowCreationData& rData, unsigned short iconID);

/**
* サブウィンドウを作成する関数
* @param[in] rData				ウィンドウ作成時の設定データ
* @param[in] rMainWinHandle		メインウィンドウのハンドル
* @return IWindowクラスのインスタンスのポインタ
*/
UniquePtr<IWindow> CreateSubWindow(const WindowCreationData& rData, const WindowHandle& rMainWinHandle);

}	// namespace sl

#endif	// SL_CREATE_IWINDOW_FUNC_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
