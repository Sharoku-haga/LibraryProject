//==================================================================================================================================//
//!< @file		dx11Window.h
//!< @brief		dx11::Windowクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DX11_WINDOW_H
#define SL_DX11_WINDOW_H

#include <windows.h>
#include "../../Common/slTypes.h"
#include "../slIWindow.h"

namespace sl
{
namespace dx11
{

//======================================================================//
//!< DirectX11のWindowクラス
//======================================================================//
class Window  : public IWindow
{

public:
	/** Constructor */
	Window(void);

	/** Desutructor */
	virtual ~Window(void);

	/**
	* 初期化関数
	* @param[in] pWinTitle	ウィンドウのタイトル
	* @param[in] winWidth	ウィンドウの幅
	* @param[in] winHeight	ウィンドウの高さ
	* @param[in] hWndParent 親のハンドル(デフォルト引数はNULL)
	* @return ウィンドウ作成が成功したかどうか true = 作成成功, false = 作成失敗
	*/
	virtual bool Initialize(t_char*  pWinTitle, int winWidth, int winHeight, HWND hWndParent = NULL);

	/** 破棄関数 */
	virtual void Finalize(void);

	/** 
	* ウィンドウハンドルを取得する関数
	* @return ウィンドウハンドル
	*/
	virtual HWND GetHwnd(void);

	/**
	* ウィンドウ更新関数
	* @return ウィンドウが破棄されたかどうか true = 破棄された false = 破棄されていない
	*/
	virtual bool Update(void);

protected:
	HWND		m_hWnd;				//!< ウィンドウハンドル
	HWND		m_hWndParent;		//!< 親ウィンドウハンドル
	MSG			m_WinMsg;			//!< メッセージ構造体	

};	// class Window 

}	// namespace dx11
}	// namespace sl

#endif	// SL_DX11_WINDOW_H
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
