//==================================================================================================================================//
//!< @file		slDIKeyboard.h
//!< @brief		sl::DIKeyboardクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/07	更新履歴：2017/10/11
//==================================================================================================================================//

#ifndef SL_DI_KEYBOARD_H
#define SL_DI_KEYBOARD_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <vector>
#include "../../slIInputDevice.h"
#include "../../../slInputDeviceDeclaration.h"

namespace sl
{

//===================================================================================//
//!< DirectInputのキーボードクラス
//===================================================================================//
class DIKeyboard : public IInputDevice
{

public:
	/** 
	* Constructor 
	* @param[in] pKeyDevice	ダイレクトインプットのキーデバイス
	*/
	explicit DIKeyboard(LPDIRECTINPUTDEVICE8 pKeyDevice);
	
	/** Destructor */
	~DIKeyboard() = default;

	/**
	* 使用するキーを登録する関数
	* この関数で登録したキーはUpdateStateで状態を更新する
	* @param[in] keyType  キーのタイプ
	*/
	void RegisterUsingKey(KEY_TYPE keyType);

	/** デバイスの状態を更新する関数 */
	virtual void UpdateState()override;

	/**
	* 指定したキーが指定した状態かどうかを確認する関数 
	* @param[in] keyType		状態を確認したいキーのタイプ
	* @param[in] checkState		指定した状態
	* @return ture→指定した状態である false→指定した状態でない
	*/
	bool CheckKeyState(KEY_TYPE keyType, INPUT_DEVICE_STATE checkState);

	/**
	* 引数のキーを使用キーとして登録したか調べる関数
	* @param[in] keyType		登録を確認したいキーのタイプ
	* @return ture→登録している false→登録していない
	*/
	bool IsRegisteredUsingKey(KEY_TYPE keyType);

private:
	static constexpr int	m_KeyTypeCount = 256;				//!< キーの種類の数 
	LPDIRECTINPUTDEVICE8	m_pDIKeyDevice;						//!< ダイレクトインプットのキーデバイス
	std::vector<KEY_TYPE>	m_UsingKey;							//!< 使用するキーの種類を格納するvector					
	INPUT_DEVICE_STATE		m_CurrentKeyState[m_KeyTypeCount];	//!< 現在のキーの状態を格納する配列
	INPUT_DEVICE_STATE		m_OldKeyState[m_KeyTypeCount];		//!< 前のキーの状態を格納する配列
	unsigned char			m_DIKeys[m_KeyTypeCount];			//!< デバイスからのキー状態を格納する配列

	/** 
	* キーの状態を更新する関数
	* @param[in] key  キーのタイプ
	*/
	void UpdateKeyState(KEY_TYPE key);

};	// class DIKeyboard

}	// namespace sl


#endif	// SL_DI_KEYBOARD_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
