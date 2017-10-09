//==================================================================================================================================//
//!< @file		slDIMouse.h		
//!< @brief		sl::DIMouseクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/07	更新履歴：2017/10/09
//==================================================================================================================================//

#ifndef SL_DI_MOUSE_H
#define SL_DI_MOUSE_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <d3dx10.h>
#include "../../../../Utility/slPoint.h"
#include "../../../../Window/slWindowDeclaration.h"
#include "../../../slInputDeviceDeclaration.h"

namespace sl
{

//===================================================================================//
//!< DirectInoutのマウスクラス
//===================================================================================//
class DIMouse
{

public:
	/** 
	* Constructor 
	* @param[in] pMouseDevice	DirextInputのマウスデバイス
	* @param[in] rHandle		ウィンドウハンドル
	*/
	DIMouse(LPDIRECTINPUTDEVICE8 pMouseDevice, const WindowHandle& rHandle);

	/** Destructor */
	~DIMouse() = default;

	/** マウスの状態を更新する関数 */
	void UpdateState();

	/**
	* Getter
	* @return マウスカーソルの座標
	*/
	const long_Point&	GetMouseCursorPos() { return m_MouseCursorPos; }

	/**
	* Getter
	* @param[in] btn	状態を取得したいマウスボタン
	* @return 指定したマウスボタンの状態
	*/
	INPUT_DEVICE_STATE GetButtonState(MOUSE_BTN_TYPE btn) { return m_CurrentBTNState[btn]; }

	/**
	* Getter
	* @return ホイールの状態
	*/
	MOUSE_WHEEL_STATE GetWheelState() { return m_WheelState; }

	/**
	* Setter
	* @param[in] マウスカーソルの座標にセットしたい値
	*/
	void SetMouseCursorPos(const int_Point& rPos);

	/**
	* マウスカーソルの描画をONかOFFにする関数.
	* @param[in] isVisible 表示するならtrue,非表示ならfalse
	*/
	void ShowMouseCursor(bool isVisible);

private:
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;										//!< DirectInputのマウスデバイス
	WindowHandle			m_WinHandle;										//!< 結びついているウィンドウハンドル
	DIMOUSESTATE			m_DIMouseState;										//!< DirectInputのマウス状態を格納する変数
	long_Point				m_MouseCursorPos;									//!< マウスのカーソル座標
	INPUT_DEVICE_STATE		m_CurrentBTNState[MOUSE_BTN_TYPE::MOUSE_BTN_MAX];	//!< 現在のマウスボタンの状態を格納する配列
	INPUT_DEVICE_STATE		m_OldBTNState[MOUSE_BTN_TYPE::MOUSE_BTN_MAX];		//!< 前のマウスのボタン状態を格納する配列
	MOUSE_WHEEL_STATE		m_WheelState;										//!< ホイールの状態

	/** マウスカーソルの座標を更新する関数 */
	void UpdateMouseCursorPos();

	/** ボタンの状態を更新する関数 */
	void UpdateButtonState();

	/** ホイールの状態を更新する関数 */
	void UpdateWheelState();

};	// class DIMouse

}	// namespace sl

#endif	// SL_DI_MOUSE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
