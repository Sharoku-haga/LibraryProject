//==================================================================================================================================//
//!< @file		slIWindow.h
//!< @brief		slIWindowクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_IWINDOW_H
#define SL_IWINDOW_H

#include <windows.h>
#include "../Common/slTypes.h"
#include "../Common/slDefine.h"

namespace sl
{

//======================================================================//
//!< Windowのインターフェイスクラス
//======================================================================//
interface IWindow 
{

public:
	/** Constructor */
	IWindow() = default;

	/** Desutructor */
	virtual ~IWindow() = default;

	SL_DISALLOW_COPY_AND_ASSIGN(IWindow);

	/**
	* 初期化関数
	* @param[in] pWinTitle	ウィンドウのタイトル
	* @param[in] winWidth	ウィンドウの幅
	* @param[in] winHeight	ウィンドウの高さ
	* @param[in] hWndParent 親のハンドル(デフォルト引数はnullptr)
	* @return ウィンドウ作成が成功したかどうか true = 作成成功, false = 作成失敗
	*/
	virtual bool Initalize(t_char*  pWinTitle, int winWidth, int winHeight, HWND hWndParent = nullptr) = 0;

	/** 破棄関数 */
	virtual void Finalize(void) = 0;

	/** 
	* ウィンドウハンドルを取得する関数
	* @return ウィンドウハンドル
	*/
	virtual HWND GetHwnd(void) = 0;

	/**
	* ウィンドウ更新関数
	* @return ウィンドウが破棄されたかどうか true = 破棄された false = 破棄されていない
	*/
	virtual bool Update(void) = 0;

};	// interface IWindow

}	// namespace sl

#endif	// SL_IWINDOW_H
	//==================================================================================================================================//
	// END OF FILE
	//==================================================================================================================================//
