//==================================================================================================================================//
//!< @file		slWinInputDeviceLibrary.h
//!< @brief		sl::WinInputDeviceLibraryクラスのへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/10
//==================================================================================================================================//

#ifndef SL_WIN_INPUT_DEVICE_LIBRARY_H
#define SL_WIN_INPUT_DEVICE_LIBRARY_H

#include <vector>
#include "../slIInputDeviceLibrary.h"

namespace sl
{

class IInputDevice;
class DIDeviceManager;
class DIKeyboard;
class DIMouse;
class XInputDeviceManager;

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

	//-----------------------------------------------------------------//
	// インプットデバイス共通関数
	//-----------------------------------------------------------------//

	/**
	* 初期化関数
	* @param[in] rHandle ウィンドウハンドル
	* @return ture→成功 false→失敗
	*/
	virtual bool Initialize(const WindowHandle& rHandle)override;

	/** 
	* インプットデバイス生成関数
	* @param[in] deviceType 作成したいデバイスタイプ
	* @return ture→生成成功 false→生成失敗
	*/
	virtual bool CreateInputDevice(INPUT_DEVICE_TYPE deviceType)override;
	
	/** デバイスの状態を更新する関数. 毎フレーム呼ぶ関数 */
	virtual void UpdateInputDeviceState()override;

	//-----------------------------------------------------------------//
	// キーデバイス関連関数
	//-----------------------------------------------------------------//

	/** 
	* クライアント側で使用するキーを登録する関数. 
	* @param[in]  key 登録したいキーID
	* @attention キーデバイスを作成していない場合はassertで止まる
	*/
	virtual void RegisterUsingKey(KEY_TYPE key)override;

	/** 
	* 指定したキーの状態を確認する関数
	* @param[in] 状態を確認したいキーのID
	* @return 指定したキーの状態
	* @attention キーデバイスを作成していない場合はassertで止まる
	*/
	virtual INPUT_DEVICE_STATE CheckKeyState(KEY_TYPE key)override;

	//-----------------------------------------------------------------//
	// マウスデバイス関連関数
	//-----------------------------------------------------------------//

	/**
	* マウスカーソルの描画をONかOFFにする関数.
	* @param[in] isVisible 表示するならtrue,非表示ならfalse
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual void ShowMouseCursor(bool isVisible)override;

	/**
	* 指定したマウスのボタンの状態を確認する関数
	* @param[in] 状態を確認したいマウスボタンのID
	* @return 指定したマウスボタンの状態
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual INPUT_DEVICE_STATE CheckMouseButtonState(MOUSE_BTN_TYPE button)override;

	/** 
	* マウスのホイールの状態を取得する関数 
	* @return マウスホイールの状態
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual MOUSE_WHEEL_STATE CheckMouseWheelState()override;

	/**
	* マウスカーソルの座標を取得する関数
	* @return マウスカーソルの座標
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual const long_Point&	GetMouseCursorPos()override;

	/**
	* マウスカーソルの座標をセットする関数
	* @param[in] マウスカーソルの座標にセットしたい値
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual void SetMouseCursorPos(const int_Point& rPos)override;

	//-----------------------------------------------------------------//
	// XInputデバイス(XBOXコントローラー)関連関数
	//-----------------------------------------------------------------//

	/**
	* XInputのデバイスを追加する関数.最大数は4
	* @return true→追加成功 false→追加失敗(すでに最大数の場合)
	*/
	virtual bool AddXIputDevice()override; 

	/**
	* XInputのデバイス数を取得する関数
	* @return XInputのデバイス数
	*/
	virtual int GetXInputDeviceCount()override;

	/**
	* 指定したXBOXコントローラーのボタンなどの状態を確認する関数
	* @param[in] actionType 状態を取得したいXBOXコントローラーのID
	* @return 指定したXBOXコントローラーのボタンなどの状態
	* @attention XIputデバイスを作成していない場合はassertで止まる
	*/
	virtual INPUT_DEVICE_STATE CheckXInputAction(XIDEVICE_ACTION_TYPE actionType)override;

private:
	DIDeviceManager*						m_pDeviceManager;			//!< DIDeviceManagerクラスのインスタンスへのポインタ
	DIKeyboard*								m_pKeyboard ;				//!< DIKeyboardクラスのインスタンスへのポインタ
	DIMouse*								m_pMouse;					//!< DIMouseクラスのインスタンスへのポインタ
	XInputDeviceManager*					m_pXInputDeviceManager;		//!< XInputDeviceManagerクラスのインスタンスへのポインタ
	std::vector<IInputDevice*>				m_pIInputDevice;			//!< IInputDeviceクラスのインスタンスへのポインタを格納したポインタ

};	// class WinInputDeviceLibrary

}	// namespace sl

#endif	//  SL_WIN_INPUT_DEVICE_LIBRARY_H


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
