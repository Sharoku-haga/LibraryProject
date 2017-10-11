//==================================================================================================================================//
//!< @file		slWinCustomizeInputManager.h
//!< @brief		sl::WinCustomizeInputManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/11	更新履歴：
//==================================================================================================================================//

#ifndef SL_WIN_CUSTOMIZE_INPUT_MANAGER_H
#define SL_WIN_CUSTOMIZE_INPUT_MANAGER_H

#include <map>
#include <vector>
#include "../../../slInputDeviceDeclaration.h"

namespace sl
{

class DIKeyboard;
class DIMouse;
class XInputDeviceManager;

//===================================================================================//
//!< WindowsにおけるInputの設定をカスタマイズし、その設定を管理するクラス<br>
//!< ここでいうInputの設定とはキーなどのInputデバイスのボタンなどに
//!< クライアント側で自由にIDを設定して使えるようにすること
//===================================================================================//
class WinCustomizeInputManager
{

public:
	/** Constructor */
	WinCustomizeInputManager();

	/** Destructor */
	~WinCustomizeInputManager() = default;

	/**
	* Setter
	* @param[in]  DIKeyboardクラスのインスタンスへのポインタ
	*/
	void SetDIKeyboard(DIKeyboard* const pKeyboard) { m_pKeyboard = pKeyboard; }
	
	/**
	* Setter
	* @param[in]  DIMouseクラスのインスタンスへのポインタ
	*/
	void SetDIMouse(DIMouse* const pMouse) { m_pMouse = pMouse; }
	
	/**
	* Setter
	* @param[in]  XInputDeviceManagerクラスのインスタンスへのポインタ
	*/
	void SetXInputDeviceManager(XInputDeviceManager* const pXInputDeviceManager) 
	{ 
		m_pXInputDeviceManager = pXInputDeviceManager; 
	}

	/** 
	* キーのカスタマイズ登録関数
	* @param[in] id			登録したいID
	* @param[in] keyType	登録したいキーの種類
	* @attention DIKeyboardをセットしていない場合はassertで止まる
	*/
	void RegisterCustomizeKey(int id, KEY_TYPE keyType);

	/** 
	* マウスボタンのカスタマイズ登録関数
	* @param[in] id			登録したいID
	* @param[in] mouseBtn	登録したいマウスのボタン
	* @attention DIMouseをセットしていない場合はassertで止まる
	*/
	void RegisterCustomizeMouseButton(int id, MOUSE_BTN_TYPE mouseBtn);

	/**
	* XInpntのアクションのカスタマイズ登録関数
	* @param[in] id				登録したいID
	* @param[in] actionType		登録したいアクションタイプ
	* @attention XInputDeviceManagerをセットしていない場合はassertで止まる
	*/
	void RegisterCustomizeXInputAction(int id, XIDEVICE_ACTION_TYPE actionType);

	/** 
	* カスタマイズインプットが指定した状態かどうか確認する関数
	* @param[in] id				登録したID
	* @param[in] checkState		チェックしたい状態
	* @param[in] deviceNum		デバイス番号.0～3まで対応. デフォルトは0.
	* @return	その状態かどうか true→指定した状態である false →指定した状態でない
	*/
	bool CheckCustomizeInputState(int id, INPUT_DEVICE_STATE checkState, int deviceNum = 0);

private:
	DIKeyboard*												m_pKeyboard;				//!< DIKeyboardクラスのインスタンスへのポインタ
	DIMouse*												m_pMouse;					//!< DIMouseクラスのインスタンスへのポインタ
	XInputDeviceManager*									m_pXInputDeviceManager;		//!< XInputDeviceManagerクラスのインスタンスへのポインタ
	std::map<int, std::vector<INPUT_DEVICE_TYPE>>			m_CustomizeDevice;			//!< カスタマイズ登録したデバイスの種類を格納したmap.intは登録ID
	std::map<int, std::vector<KEY_TYPE>>					m_CustomizeKey;				//!< カスタマイズ登録したキーを格納したmap.intは登録ID
	std::map<int, std::vector<MOUSE_BTN_TYPE>>				m_CustomizeMouseButton;		//!< カスタマイズ登録したマウスボタンを格納したmap.intは登録ID
	std::map<int, std::vector<XIDEVICE_ACTION_TYPE>>		m_CustomizeXInputAction;	//!< カスタマイズI登録したXInpntのアクションを格納したmap.intは登録ID

	/** デバイスのカスタマイズ登録関数 */
	void RegisterCustomizeDevice(int id, INPUT_DEVICE_TYPE deviceType);

};	// class WinCustomizeInputManager

}	// namespace sl

#endif	// SL_WIN_CUSTOMIZE_INPUT_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
