//==================================================================================================================================//
//!< @file		slDXWindow.h
//!< @brief		sl::DXWindowクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/05	更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_DX_WINDOW_H
#define SL_DX_WINDOW_H

#include <windows.h>
#include "../slIWindow.h"
#include "../../../Utility/slRect.h"
#include "../../slWindowDeclaration.h"

namespace sl
{

struct WindowHandle;

//===================================================================================//
//!< DirectXのウィンドウクラス
//===================================================================================//
class DXWindow : public IWindow
{

public:
	/** 
	* Constructor
	* @param[in] hWnd			ウィンドウハンドル
	*/
	explicit DXWindow(HWND hWnd);

	/** Destructor */
	virtual ~DXWindow();

	/**
	* ウィンドウ更新関数
	* @return ウィンドウが終了したかどうか ture→終了した false→終了していない 
	*/
	virtual bool Update()override;

	/**
	* ウィンドウハンドルを取得する関数
	* @return ウィンドウハンドル
	*/
	virtual WindowHandle GetWindowHandle() const override;

private:
	HWND		m_hWnd;				//!< ウィンドウハンドル
	MSG			m_WinMsg;			//!< メッセージ構造体	
	
};	// class DXWindow

}	// namespace sl

#endif	// SL_DX_WINDOW_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
