//==================================================================================================================================//
//!< @file		slWinInputDeviceLibrary.h
//!< @brief		sl::WinInputDeviceLibraryクラスのへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：
//==================================================================================================================================//

#ifndef SL_WIN_INPUT_DEVICE_LIBRARY_H
#define SL_WIN_INPUT_DEVICE_LIBRARY_H

#include "../slIInputDeviceLibrary.h"

namespace sl
{

class DIDeviceManager;

//===================================================================================//
//!< Windowsにおけるインプットデバイスライブラリのクラス
//===================================================================================//
class WinInputDeviceLibrary : public IInputDeviceLibrary
{

public:
	/** Constructor */
	WinInputDeviceLibrary();
	
	/** Destructor */
	~WinInputDeviceLibrary();

	/**
	* 初期化関数
	* @param[in] rHandle ウィンドウハンドル
	* @return ture→成功 false→失敗
	*/
	virtual bool Initialize(const WindowHandle& rHandle)override;

private:
	DIDeviceManager*	m_pDeviceManager;		//!< DIDeviceManagerクラスのインスタンスへのポインタ

};	// class WinInputDeviceLibrary

}	// namespace sl

#endif	//  SL_WIN_INPUT_DEVICE_LIBRARY_H


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
