//==================================================================================================================================//
//!< @file		diGamePad.h
//!< @brief		di::GamePadクラスヘッダ
//!< @author	T.Haga
//!< @todo		実装は後で行う
//==================================================================================================================================//

#ifndef SL_DI_GAMEPAD_H
#define SL_DI_GAMEPAD_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <Windows.h>
#include "../../../Common/slInputEnum.h"

namespace sl
{
namespace di
{

//======================================================================//
//!< DirectInputのGamePaddクラス
//======================================================================//
class GamePad
{

public:
	/** Constructor */
	GamePad(void);

	/** Destructor */
	~GamePad(void);

	/** 
	* 初期化関数
	* @param[in] pDInput8	ダイレクトインプット
	* @param[in] hWnd		ウィンドウハンドル
	* @return 結果 true→成功 false→失敗
	*/
	bool Initialize(LPDIRECTINPUT8 pDInput8, HWND hWnd);

	/** 更新関数 */
	void Update(void);

	/** ボタンの状態をチェックする関数 */
	void CheckBtn();

private:
	LPDIRECTINPUT8						m_pDInput8;					//!< DirectInputDevice
	LPDIRECTINPUTDEVICE8				m_pPadDevice;				//!< ゲームパッドデバイス格納用
	DIJOYSTATE							m_DiJoyState;				//!< ジョイスティック構造体

};

#endif	// SL_DI_GAMEPAD_H

}	// namespace di 
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
