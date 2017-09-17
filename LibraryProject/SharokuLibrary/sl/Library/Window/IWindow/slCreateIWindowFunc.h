//==================================================================================================================================//
//!< @file		slCreateIWindowFunc.h
//!< @brief		ウィンドウを生成する関数のヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/05	更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_CREATE_IWINDOW_FUNC_H
#define SL_CREATE_IWINDOW_FUNC_H

#include "../../Utility/slTypes.h"
#include "../../Utility/slDefine.h"
#include "../slWindowDeclaration.h"
#include "../../SmartPointer/UniquePtr/slUniquePtr.h"


namespace sl
{

interface IWindow;

/**
* メインウィンドウを作成する関数
* 通常時に使用する
* @param[in] pWinName	ウィンドウネーム
* @param[in] winWidth	ウィンドウの横幅
* @param[in] winHeight	ウィンドウの縦幅
* @return IWindowクラスのインスタンスのポインタ
*/
UniquePtr<IWindow> CreateMainWindow(t_char* pWinName, int winWidth, int winHeight);

/**
* メインウィンドウを作成する関数
* アイコンも作成するときに使用する
* @param[in] pWinName	ウィンドウネーム
* @param[in] winWidth	ウィンドウの横幅
* @param[in] winHeight	ウィンドウの縦幅
* @param[in] iconID		アイコンID
* @return IWindowクラスのインスタンスのポインタ
*/
UniquePtr<IWindow> CreateMainWindow(t_char* pWinName, int winWidth, int winHeight, unsigned short iconID);

/**
* サブウィンドウを作成する関数
* @param[in] pWinName			ウィンドウネーム
* @param[in] winWidth			ウィンドウの横幅
* @param[in] winHeight			ウィンドウの縦幅
* @param[in] rMainWinHandle		メインウィンドウのハンドル
* @return IWindowクラスのインスタンスのポインタ
*/
UniquePtr<IWindow> CreateSubWindow(t_char* pWinName, int winWidth, int winHeight, const WindowHandle& rMainWinHandle);

}	// namespace sl

#endif	// SL_CREATE_IWINDOW_FUNC_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
