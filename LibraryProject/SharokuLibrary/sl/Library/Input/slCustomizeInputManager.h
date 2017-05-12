//==================================================================================================================================//
//!< @file		slCustomizeInputManager.h
//!< @brief		sl::CustomizeInputManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_CUSTOMIZE_INPUT_MANAGER_H
#define SL_CUSTOMIZE_INPUT_MANAGER_H

#include <map>
#include "../../Common/slInputEnum.h"

namespace sl
{

namespace di
{

class InputManager;
class KeyDevice;

}	// namespace di

namespace xi
{

class GamePad;

}

//======================================================================//
//!< Inputの設定をカスタマイズし、その設定を管理するクラス<br>
//!< ここでいうInputの設定とはキーなどのInputデバイスのボタンなどに
//!< クライアント側で自由にIDを設定して使えるようにすること
//======================================================================//
class CustomizeInputManager
{

public:

	/** 
	* Contructor
	* @param[in] pInputManager di::InputManagerのインスタンスへのポインタ
	* @param[in] pGamePad	   xi::GamePadのインスタンスへのポインタ
	*/
	CustomizeInputManager(di::InputManager* pInputManager, xi::GamePad* pGamePad);

	/** Destructor */
	~CustomizeInputManager(void);

	/** 
	* 登録関数
	* @param[in] ID			登録したいID
	* @param[in] device		デバイスタイプ
	* @param[in] inputType	登録したいインプットタイプ
	*/
	void RegisterCustomizeType(int ID, HID_TYPE device, int inputType);

	/** 
	* 状態チェック関数
	* @param[in] ID			登録したID
	* @param[in] deviceNum	デバイス番号.デフォルトは0
	*/
	DEVICE_STATE CheckState(int ID, int deviceNum = 0);

private:
	/** カスタマイズ情報構造体 */
	struct CUSTOMIZE_INFO
	{
		HID_TYPE	m_DeviceType;			//!< デバイスタイプ
		int			m_InputType;			//!< インプットタイプ
	};

	di::KeyDevice*					m_pKeyDevice;			//!< di::KeyDeviceクラスのインスタンスへのポインタ
	xi::GamePad*					m_pXiGamePad;			//!< xi::GamePadクラスのインスタンスへのポインタ
	std::map<int, CUSTOMIZE_INFO>	m_CustomizeInfos;		//!< カスタマイズした情報を格納したmap

};

}	// namespace sl

#endif	//SL_CUSTOMIZE_INPUT_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
