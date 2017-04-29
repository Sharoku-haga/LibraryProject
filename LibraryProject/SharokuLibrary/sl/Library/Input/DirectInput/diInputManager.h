//==================================================================================================================================//
//!< @file		diInputManager.cpp
//!< @brief		di::InputManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DI_INPUT_MANAGER_H
#define SL_DI_INPUT_MANAGER_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <windows.h>
#include "../../../Common/slInputEnum.h"

namespace sl
{
namespace di
{

class KeyDevice;
class GamePad;

//======================================================================//
//!< DirectInputのInputManagerクラス
//======================================================================//
class InputManager
{

public:
	/** Constructor */
	InputManager(void);

	/** Destructor */
	~InputManager(void);

	/** 
	* 初期化関数 
	* @param[in] hWnd	ウィンドウハンドル
	* @return 結果 true→成功 false →失敗
	*/
	bool Initialize(HWND hWnd);

	/** デバイス更新関数 */
	void Update(void);

	/** 
	* キーの状態確認関数 
	* @param[in] keyID キーのID slInputEnum.hのKEY_TYPE
	*/
	DEVICE_STATE CheckKey(int keyID);

	/**
	* キーボードデバイス取得関数
	* @return キーボードデバイス
	*/
	KeyDevice* GetKeyDevice(void) { return m_pKeyDevice; }

private:
	LPDIRECTINPUT8					m_pDInput8;						//!< DirectInputデバイス
	HWND							m_hWnd;							//!< ウィンドウハンドル
	KeyDevice*						m_pKeyDevice;					//!< KeyDeviceクラスのインスタンスへのポインタ
	GamePad*						m_pGamePad;						//!< GamePadクラスのインスタンスへのポインタ

};

}	// namespace di 
}	// namespace sl

#endif // SL_DI_INPUT_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
