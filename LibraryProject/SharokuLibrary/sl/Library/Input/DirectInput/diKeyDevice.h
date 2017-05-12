//==================================================================================================================================//
//!< @file		diKeyDevice.h
//!< @brief		di::KeyDeviceクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DI_KETDEVICE_H
#define SL_DI_KETDEVICE_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <Windows.h>
#include "../../../Common/slInputEnum.h"

namespace sl
{
namespace di
{

//======================================================================//
//!< DirectInputのキーボードデバイスクラス
//======================================================================//
class KeyDevice
{

public:
	/** Constructor */
	KeyDevice(void); 

	/** Destructor */
	~KeyDevice(void);

	/** 
	* 初期化関数
	* @param[in] pDInput8	ダイレクトインプット
	* @param[in] hWnd		ウィンドウハンドル
	* @return 結果 true→成功 false→失敗
	*/
	bool Initialize(LPDIRECTINPUT8 pDInput8, HWND hWnd);

	/** 更新関数 */
	void Update(void);

	/** 
	* チェック関数 
	* @param[in] keyID キーのID slInputEnum.hのKEY_TYPE
	* @return キーの状態
	*/
	DEVICE_STATE	CheckKey(int keyID);

private:
	static const int				m_KeyStateNum = 256;				//!< キーの種類
	LPDIRECTINPUT8					m_pDInput8;							//!< DirectInputデバイス
	LPDIRECTINPUTDEVICE8			m_pKeyDevice;						//!< キーボードデバイス
	BYTE							m_DIKs[m_KeyStateNum];				//!< DIKを格納する変数
	DEVICE_STATE					m_CurrentKeyState[m_KeyStateNum];	//!< 現在のキーの状態を格納する変数
	DEVICE_STATE					m_OldKeyState[m_KeyStateNum];		//!< 前のキーの状態を格納する変数

	/**
	* キーの状態を確認する関数	
	* @param[in] keyID キーのID slInputEnum.hのKEY_TYPE
	*/
	void CheckState(int keyID);
};

}	// namespace di 
}	// namespace sl

#endif	// SL_DI_KETDEVICE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
