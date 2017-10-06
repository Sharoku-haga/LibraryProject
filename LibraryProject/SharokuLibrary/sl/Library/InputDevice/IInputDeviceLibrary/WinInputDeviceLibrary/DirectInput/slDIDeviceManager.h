//==================================================================================================================================//
//!< @file		slDIDeviceManager.h
//!< @brief		sl::DIDeviceManagerクラスのへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：
//==================================================================================================================================//

#ifndef SL_DI_DEVICE_MANAGER_H
#define SL_DI_DEVICE_MANAGER_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include "../../../../Window/slWindowDeclaration.h"

namespace sl
{

//===================================================================================//
//!< DirextInputデバイス関連を管理するクラス
//===================================================================================//
class DIDeviceManager
{

public:
	/** Constructor */
	DIDeviceManager();

	/** Destructor */
	~DIDeviceManager();

	/**
	* 初期化関数
	* @param[in] rHandle ウィンドウハンドル
	* @return true→成功 false→失敗
	*/
	bool Initialize(const WindowHandle& rHandle);

	/** 
	* ダイレクトインプットのキーデバイスを生成する関数 
	* @return キーデバイス	生成失敗した場合はNULLが返ってくる
	*/
	LPDIRECTINPUTDEVICE8	CreateDIKeyDevice();

	/**
	* ダイレクトインプットのマウスデバイスを生成する関数
	* @return マウスデバイス 生成失敗した場合はNULLが返ってくる
	*/
	LPDIRECTINPUTDEVICE8	CreateDIMouseDevice();

private:
	LPDIRECTINPUT8					m_pDInput8;					//!< DirectInputデバイス
	WindowHandle					m_Handle;					//!< ウィンドウハンドル

};	// class DIDeviceManager

} // namespace sl

#endif	// SL_DI_DEVICE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
