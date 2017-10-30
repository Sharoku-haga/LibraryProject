//==================================================================================================================================//
//!< @file		slIInputDeviceLibrary.h
//!< @brief		sl::IInputDeviceLibraryインターフェイスのへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/11
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
	static IInputDeviceLibrary& Instance();

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
	* 指定したキーが指定した状態かどうかを確認する関数 
	* @param[in] key			状態を確認したいキー
	* @param[in] checkState		指定した状態
	* @return ture→指定した状態である false→指定した状態でない
	*/
	virtual bool CheckKeyState(KEY_TYPE key, INPUT_DEVICE_STATE checkState) = 0;

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
	* 指定したマウスのボタンが指定した状態かどうかを確認する関数 
	* @param[in] button			状態を確認したいマウスボタン
	* @param[in] checkState		指定した状態
	* @return ture→指定した状態である false→指定した状態でない
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual bool CheckMouseButtonState(MOUSE_BTN_TYPE button, INPUT_DEVICE_STATE checkState) = 0;

	/**
	* マウスホイールが指定した状態かどうかを確認する関数 
	* @param[in] checkState		指定した状態
	* @return ture→指定した状態である false→指定した状態でない
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual bool CheckMouseWheelState(MOUSE_WHEEL_STATE checkState) = 0;

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
	* 指定したXInputアクション(XBOXコントローラーのボタンなど)が指定した状態かどうかを確認する関数 
	* @param[in] actionType		状態を確認したいXInputアクション
	* @param[in] checkState		指定した状態
	* @param[in] deviceNum		XInputデバイス番号.0～3を指定できる(デフォルトは0)
	* @return ture→指定した状態である false→指定した状態でない
	* @attention XInputデバイスを作成していない場合はassertで止まる
	*/
	virtual bool CheckXInputActionState(XIDEVICE_ACTION_TYPE actionType, INPUT_DEVICE_STATE checkState
								, unsigned int deviceNum = 0) = 0;

	//-----------------------------------------------------------------//
	//	インプットデバイスカスタマイズ関連関数
	//	ここでいうカスタマイズとはキーなどのInputデバイスのボタンなどに
	//	クライアント側で自由にIDを設定して使えるようにすること
	//-----------------------------------------------------------------//

	/** 
	* キーのカスタマイズ登録関数
	* @param[in] id			登録したいID
	* @param[in] key		登録したいキー
	* @attention キーデバイスを作成していない場合はassertで止まる
	*/
	virtual void RegisterCustomizeKey(int id, KEY_TYPE key) = 0;

	/** 
	* マウスボタンのカスタマイズ登録関数
	* @param[in] id			登録したいID
	* @param[in] mouseBtn	登録したいマウスのボタン
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual void RegisterCustomizeMouseButton(int id, MOUSE_BTN_TYPE mouseBtn) = 0;

	/**
	* XInpntのアクションのカスタマイズ登録関数
	* @param[in] id				登録したいID
	* @param[in] actionType		登録したいアクションタイプ
	* @attention XInputデバイスを作成していない場合はassertで止まる
	*/
	virtual void RegisterCustomizeXInputAction(int id, XIDEVICE_ACTION_TYPE actionType) = 0;

	/** 
	* カスタマイズしたインプットデバイスが指定した状態かどうか確認する関数
	* @param[in] id				登録したID
	* @param[in] checkState		チェックしたい状態
	* @param[in] deviceNum		デバイス番号.0～3まで対応. デフォルトは0.
	* @return	その状態かどうか true→指定した状態である false →指定した状態でない
	*/
	virtual bool CheckCustomizeInputState(int id, INPUT_DEVICE_STATE checkState
										, int deviceNum = 0) = 0;

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
