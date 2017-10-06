//==================================================================================================================================//
//!< @file		slIInputDeviceLibrary.h
//!< @brief		sl::IInputDeviceLibraryインターフェイスのへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：
//==================================================================================================================================//

#ifndef SL_IINPUT_DEVICE_LIBRARY_H
#define SL_IINPUT_DEVICE_LIBRARY_H

#include "../../Utility/slDefine.h"

namespace sl
{

struct WindowHandle;

//===================================================================================//
//!< インプットデバイスライブラリのインターフェイスクラス
//===================================================================================//
interface IInputDeviceLibrary
{

public:
	/** 実体を取得する関数 */
	IInputDeviceLibrary& Instance();

	/**
	* 初期化関数
	* @param[in] rHandle ウィンドウハンドル
	* @return ture→成功 false→失敗
	*/
	virtual bool Initialize(const WindowHandle& rHandle) = 0;

protected:
	/** Constructor */
	IInputDeviceLibrary() = default;

	/** Destructor */
	virtual ~IInputDeviceLibrary() = default;

};	// interface IInputDeviceLibrary

}	// namespace sl

#endif	// SL_IINPUT_DEVICE_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
