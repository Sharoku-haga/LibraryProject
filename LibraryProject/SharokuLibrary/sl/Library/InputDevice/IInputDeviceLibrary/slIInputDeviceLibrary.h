//==================================================================================================================================//
//!< @file		slIInputDeviceLibrary.h
//!< @brief		sl::IInputDeviceLibraryインターフェイスのへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/10
//==================================================================================================================================//

#ifndef SL_IINPUT_DEVICE_LIBRARY_H
#define SL_IINPUT_DEVICE_LIBRARY_H

#include "../../Utility/slDefine.h"
#include "../../Utility/slPoint.h"
#include "../slInputDeviceDeclaration.h"

namespace sl
{

struct WindowHandle;

//===================================================================================//
//!< インプットデバイスライブラリのインターフェイスクラス
//===================================================================================//
interface IInputDeviceLibrary
{

public:
	//-----------------------------------------------------------------//
	// インプットデバイス共通関数
	//-----------------------------------------------------------------//

	/** 
	* 実体を取得する関数 
	* @return インプットデバイスライブラリこのクラスを継承したクラス
	*/
	IInputDeviceLibrary& Instance();

	/**
	* 初期化関数
	* @param[in] rHandle ウィンドウハンドル
	* @return ture→成功 false→失敗
	*/
	virtual bool Initialize(const WindowHandle& rHandle) = 0;

	/** 
	* インプットデバイス生成関数
	* @param[in] deviceType 作成したいデバイスタイプ
	* @return ture→生成成功 false→生成失敗
	*/
	virtual bool CreateInputDevice(INPUT_DEVICE_TYPE deviceType) = 0;
	
	/** デバイスの状態を更新する関数. 毎フレーム呼ぶ関数 */
	virtual void UpdateInputDeviceState() = 0;

	//-----------------------------------------------------------------//
	// キーデバイス関連関数
	//-----------------------------------------------------------------//

	/** 
	* クライアント側で使用するキーを登録する関数. 
	* @param[in]  key 登録したいキーID
	* @attention キーデバイスを作成していない場合はassertで止まる
	*/
	virtual void RegisterUsingKey(KEY_TYPE key) = 0;

	/** 
	* 指定したキーの状態を確認する関数
	* @param[in] 状態を確認したいキーのID
	* @return 指定したキーの状態
	* @attention キーデバイスを作成していない場合はassertで止まる
	*/
	virtual INPUT_DEVICE_STATE CheckKeyState(KEY_TYPE key) = 0;

	//-----------------------------------------------------------------//
	// マウスデバイス関連関数
	//-----------------------------------------------------------------//

	/**
	* マウスカーソルの描画をONかOFFにする関数.
	* @param[in] isVisible 表示するならtrue,非表示ならfalse
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual void ShowMouseCursor(bool isVisible) = 0;

	/**
	* 指定したマウスのボタンの状態を確認する関数
	* @param[in] 状態を確認したいマウスボタンのID
	* @return 指定したマウスボタンの状態
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual INPUT_DEVICE_STATE CheckMouseButtonState(MOUSE_BTN_TYPE button) = 0;

	/** 
	* マウスのホイールの状態を取得する関数 
	* @return マウスホイールの状態
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual MOUSE_WHEEL_STATE CheckMouseWheelState() = 0;

	/**
	* マウスカーソルの座標を取得する関数
	* @return マウスカーソルの座標
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual const long_Point&	GetMouseCursorPos() = 0;

	/**
	* マウスカーソルの座標をセットする関数
	* @param[in] マウスカーソルの座標にセットしたい値
	*/
	virtual void SetMouseCursorPos(const int_Point& rPos) = 0;

	//-----------------------------------------------------------------//
	// XInputデバイス(XBOXコントローラー)関連関数
	//-----------------------------------------------------------------//

	/**
	* XInputのデバイスを追加する関数.最大数は4
	* @return true→追加成功 false→追加失敗(すでに最大数の場合)
	*/
	virtual bool AddXIputDevice() = 0; 

	/**
	* XInputのデバイス数を取得する関数
	* @return XInputのデバイス数
	*/
	virtual int GetXInputDeviceCount() = 0;

	/**
	* 指定したXBOXコントローラーのボタンなどの状態を確認する関数
	* @param[in] actionType 状態を取得したいXBOXコントローラーのID
	* @return 指定したXBOXコントローラーのボタンなどの状態
	* @attention XIputデバイスを作成していない場合はassertで止まる
	*/
	virtual INPUT_DEVICE_STATE CheckXInputAction(XIDEVICE_ACTION_TYPE actionType) = 0;

protected:
	/** Constructor */
	IInputDeviceLibrary() = default;

	/** Destructor */
	virtual ~IInputDeviceLibrary() = default;

	SL_DISALLOW_COPY_AND_ASSIGN(IInputDeviceLibrary);

};	// interface IInputDeviceLibrary

}	// namespace sl

#endif	// SL_IINPUT_DEVICE_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
