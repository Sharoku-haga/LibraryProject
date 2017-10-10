//==================================================================================================================================//
//!< @file		slWinInputDeviceLibrary.h
//!< @brief		sl::WinInputDeviceLibraryクラスのへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/11
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
class WinCustomizeInputManager;

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
	* 指定したキーが指定した状態かどうかを確認する関数 
	* @param[in] key			状態を確認したいキー
	* @param[in] checkState		指定した状態
	* @return ture→指定した状態である false→指定した状態でない
	* @attention キーデバイスを作成していない場合はassertで止まる
	*/
	virtual bool CheckKeyState(KEY_TYPE key, INPUT_DEVICE_STATE checkState)override;

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
	* 指定したマウスのボタンが指定した状態かどうかを確認する関数 
	* @param[in] button			状態を確認したいマウスボタン
	* @param[in] checkState		指定した状態
	* @return ture→指定した状態である false→指定した状態でない
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual bool CheckMouseButtonState(MOUSE_BTN_TYPE button, INPUT_DEVICE_STATE checkState)override;

	/**
	* マウスホイールが指定した状態かどうかを確認する関数 
	* @param[in] checkState		指定した状態
	* @return ture→指定した状態である false→指定した状態でない
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual bool CheckMouseWheelState(MOUSE_WHEEL_STATE checkState)override;

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
	* 指定したXInputアクション(XBOXコントローラーのボタンなど)が指定した状態かどうかを確認する関数 
	* @param[in] actionType		状態を確認したいXInputアクション
	* @param[in] checkState		指定した状態
	* @param[in] deviceNum		XInputデバイス番号.0～3を指定できる(デフォルトは0)
	* @return ture→指定した状態である false→指定した状態でない
	* @attention XInputデバイスを作成していない場合はassertで止まる
	*/
	virtual bool CheckXInputActionState(XIDEVICE_ACTION_TYPE actionType, INPUT_DEVICE_STATE checkState
								, unsigned int deviceNum = 0)override;

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
	virtual void RegisterCustomizeKey(int id, KEY_TYPE key)override;

	/** 
	* マウスボタンのカスタマイズ登録関数
	* @param[in] id			登録したいID
	* @param[in] mouseBtn	登録したいマウスのボタン
	* @attention マウスデバイスを作成していない場合はassertで止まる
	*/
	virtual void RegisterCustomizeMouseButton(int id, MOUSE_BTN_TYPE mouseBtn)override;

	/**
	* XInpntのアクションのカスタマイズ登録関数
	* @param[in] id				登録したいID
	* @param[in] actionType		登録したいアクションタイプ
	* @attention XInputデバイスを作成していない場合はassertで止まる
	*/
	virtual void RegisterCustomizeXInputAction(int id, XIDEVICE_ACTION_TYPE actionType)override;

	/** 
	* カスタマイズしたインプットデバイスが指定した状態かどうか確認する関数
	* @param[in] id				登録したID
	* @param[in] checkState		チェックしたい状態
	* @param[in] deviceNum		デバイス番号.0～3まで対応. デフォルトは0.
	* @return	その状態かどうか true→指定した状態である false →指定した状態でない
	*/
	virtual bool CheckCustomizeInputState(int id, INPUT_DEVICE_STATE checkState
										, int deviceNum = 0)override;

private:
	DIDeviceManager*						m_pDeviceManager;			//!< DIDeviceManagerクラスのインスタンスへのポインタ
	DIKeyboard*								m_pKeyboard ;				//!< DIKeyboardクラスのインスタンスへのポインタ
	DIMouse*								m_pMouse;					//!< DIMouseクラスのインスタンスへのポインタ
	XInputDeviceManager*					m_pXInputDeviceManager;		//!< XInputDeviceManagerクラスのインスタンスへのポインタ
	WinCustomizeInputManager*				m_pCustomizeInputManager;	//!< WinCustomizeInputManagerクラスのインスタンスへのポインタ
	std::vector<IInputDevice*>				m_pIInputDevice;			//!< IInputDeviceクラスのインスタンスへのポインタを格納したポインタ

};	// class WinInputDeviceLibrary

}	// namespace sl

#endif	//  SL_WIN_INPUT_DEVICE_LIBRARY_H


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
