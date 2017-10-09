﻿//==================================================================================================================================//
//!< @file		slXInputDeviceManager.h
//!< @brief		sl::XInputDeviceManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/07	更新履歴：2017/10/09
//==================================================================================================================================//

#ifndef SL_XINPUT_DEVICE_MANAGER_H
#define SL_XINPUT_DEVICE_MANAGER_H

#include <windows.h>
#include <XInput.h>
#include <vector>
#include "../../../slInputDeviceDeclaration.h"

namespace sl
{

//===================================================================================//
//!< XIpuntDevice(XBOXコントローラー)を管理するクラス
//===================================================================================//
class XInputDeviceManager
{

public:
	/** Constructor */
	XInputDeviceManager();

	/** Destructor */
	~XInputDeviceManager() = default;

	/** 
	* デバイス(コントローラー)の数を追加する関数 
	* 最大数(4)を超える場合は追加されない
	*/
	void AddDevice();

	/** 状態を更新する関数 */
	void UpdateDeviceState();

	/**
	* Getter
	* @return デバイスの数
	*/
	unsigned int GetDeviceCount() { return m_Devices.size(); }

	/**
	* Getter
	* @param[in] actionTypeID	状態を取得したいアクションID
	* @param[in] deviceNum		デバイス番号.0～3を指定できる(デフォルトは0)
	*/
	INPUT_DEVICE_STATE GetDeviceState(XIDEVICE_ACTION_TYPE actionTypeID, unsigned int deviceNum = 0);

private:
	/** デバイスの状態を格納する構造体 */
	struct DEVICE_STATE
	{
		XINPUT_STATE	m_XIState;			//!< XInputState
		bool			m_IsConnected;		//!< 接続しているかどうかののフラグ
	};	// struct DEVICE_STATE

	static constexpr int							m_DeviceCountMaxVal = 4;			//!< デバイスの最大数
	std::vector<DEVICE_STATE>						m_Devices;							//!< デバイス
	std::vector<std::vector<INPUT_DEVICE_STATE>>	m_CurrentDeviceState;				//!< 現在のボタンや部位の状態
	std::vector<std::vector<INPUT_DEVICE_STATE>>	m_OldDeviceState;					//!< 前のボタンや部位の状態

	/** ボタンの状態を更新する関数 */
	void UpdateButtonState(int deviceNum);

	/** ボタン以外の部分の状態を更新する関数 */
	void UpdatePartState(int deviceNum);

	/** 
	* 状態を更新する関数 
	* @param[in] deviceNum		デバイス番号
	* @param[in] actionTypeID	状態を更新したいアクションID
	* @param[in] isUsed			引数2のアクションを使用したかどうかのフラグ
	*/
	void UpdateState(int deviceNum, int actionTypeID, bool isUsed);
		
};	// class XInputDeviceManager

} // namespace sl

#endif	// SL_XINPUT_DEVICE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//