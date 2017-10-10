//==================================================================================================================================//
//!< @file		slInputDeviceDeclaration.h
//!< @brief		インプットデバイス関連の宣言などをまとめたへッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/09
//==================================================================================================================================//

#ifndef SL_INPUT_DEVICE_DECLARATION_H
#define SL_INPUT_DEVICE_DECLARATION_H

namespace sl
{

//===================================================================================//
//!< InputDeviceLibrary共通
//===================================================================================//

/** インプットデバイスタイプの列挙 */
enum INPUT_DEVICE_TYPE
{
	KEYBOARD,			//!< キーボード
	MOUSE,				//!< マウス
	XINPUT_DEVICE,		//!< XInputデバイス
};	// enum INPUT_DEVICE_TYPE


/** インプットデバイスの状態の列挙 */
enum INPUT_DEVICE_STATE
{
	ON,				//!< 押している状態が続いている
	OFF,			//!< 離している状態が続いている
	PUSH,			//!< 押す状態
	RELEASE,		//!< 離れる状態
	NONE,			//!< 何も設定しない状態。初期化で使用
};	// enum INPUT_DEVICE_STATE

//===================================================================================//
//!< キーデバイス関連
//===================================================================================//

/** キーの種類の列挙 */
enum KEY_TYPE
{
	K_ESCAPE		  = 0x01,
	K_1               = 0x02,
	K_2               = 0x03,
	K_3               = 0x04,
	K_4               = 0x05,
	K_5               = 0x06,
	K_6               = 0x07,
	K_7               = 0x08,
	K_8               = 0x09,
	K_9               = 0x0A,
	K_0               = 0x0B,
	K_MINUS           = 0x0C,    
	K_EQUALS          = 0x0D,
	K_BACK            = 0x0E,    
	K_TAB             = 0x0F,
	K_Q               = 0x10,
	K_W               = 0x11,
	K_E               = 0x12,
	K_R               = 0x13,
	K_T               = 0x14,
	K_Y               = 0x15,
	K_U               = 0x16,
	K_I               = 0x17,
	K_O               = 0x18,
	K_P               = 0x19,
	K_LBRACKET        = 0x1A,
	K_RBRACKET        = 0x1B,
	K_RETURN          = 0x1C,    
	K_LCONTROL        = 0x1D,
	K_A               = 0x1E,
	K_S               = 0x1F,
	K_D               = 0x20,
	K_F               = 0x21,
	K_G               = 0x22,
	K_H               = 0x23,
	K_J               = 0x24,
	K_K               = 0x25,
	K_L               = 0x26,
	K_SEMICOLON       = 0x27,
	K_APOSTROPHE      = 0x28,
	K_GRAVE           = 0x29,    
	K_LSHIFT          = 0x2A,
	K_BACKSLASH       = 0x2B,
	K_Z               = 0x2C,
	K_X               = 0x2D,
	K_C               = 0x2E,
	K_V               = 0x2F,
	K_B               = 0x30,
	K_N               = 0x31,
	K_M               = 0x32,
	K_COMMA           = 0x33,
	K_PERIOD          = 0x34,    
	K_SLASH           = 0x35,    
	K_RSHIFT          = 0x36,
	K_MULTIPLY        = 0x37,    
	K_LMENU           = 0x38,    
	K_SPACE           = 0x39,
	K_CAPITAL         = 0x3A,
	K_F1              = 0x3B,
	K_F2              = 0x3C,
	K_F3              = 0x3D,
	K_F4              = 0x3E,
	K_F5              = 0x3F,
	K_F6              = 0x40,
	K_F7              = 0x41,
	K_F8              = 0x42,
	K_F9              = 0x43,
	K_F10             = 0x44,
	K_NUMLOCK         = 0x45,
	K_SCROLL          = 0x46,    
	K_NUMPAD7         = 0x47,
	K_NUMPAD8         = 0x48,
	K_NUMPAD9         = 0x49,
	K_SUBTRACT        = 0x4A,    
	K_NUMPAD4         = 0x4B,
	K_NUMPAD5         = 0x4C,
	K_NUMPAD6         = 0x4D,
	K_ADD             = 0x4E,    
	K_NUMPAD1         = 0x4F,
	K_NUMPAD2         = 0x50,
	K_NUMPAD3         = 0x51,
	K_NUMPAD0         = 0x52,
	K_DECIMAL         = 0x53,    
	K_OEM_102         = 0x56,    
	K_F11             = 0x57,
	K_F12             = 0x58,
	K_F13             = 0x64,    
	K_F14             = 0x65,    
	K_F15             = 0x66,    
	K_KANA            = 0x70,    
	K_ABNT_C1         = 0x73,    
	K_CONVERT         = 0x79,    
	K_NOCONVERT       = 0x7B,    
	K_YEN             = 0x7D,    
	K_ABNT_C2         = 0x7E,    
	K_NUMPADEQUALS    = 0x8D,    
	K_PREVTRACK       = 0x90,    
	K_AT              = 0x91,    
	K_COLON           = 0x92,    
	K_UNDERLINE       = 0x93,    
	K_KANJI           = 0x94,    
	K_STOP            = 0x95,    
	K_AX              = 0x96,    
	K_UNLABELED       = 0x97,    
	K_NEXTTRACK       = 0x99,    
	K_NUMPADENTER     = 0x9C,    
	K_RCONTROL        = 0x9D,
	K_MUTE            = 0xA0,    
	K_CALCULATOR      = 0xA1,    
	K_PLAYPAUSE       = 0xA2,    
	K_MEDIASTOP       = 0xA4,    
	K_VOLUMEDOWN      = 0xAE,    
	K_VOLUMEUP        = 0xB0,    
	K_WEBHOME         = 0xB2,    
	K_NUMPADCOMMA     = 0xB3,    
	K_DIVIDE          = 0xB5,    
	K_SYSRQ           = 0xB7,
	K_RMENU           = 0xB8,    
	K_PAUSE           = 0xC5,    
	K_HOME            = 0xC7,    
	K_UP              = 0xC8,    
	K_PRIOR           = 0xC9,    
	K_LEFT            = 0xCB,    
	K_RIGHT           = 0xCD,    
	K_END             = 0xCF,    
	K_DOWN            = 0xD0,    
	K_NEXT            = 0xD1,    
	K_INSERT          = 0xD2,    
	K_DELETE          = 0xD3,    
	K_LWIN            = 0xDB,    
	K_RWIN            = 0xDC,    
	K_APPS            = 0xDD,    
	K_POWER           = 0xDE,    
	K_SLEEP           = 0xDF,    
	K_WAKE            = 0xE3,    
	K_WEBSEARCH       = 0xE5,    
	K_WEBFAVORITES    = 0xE6,    
	K_WEBREFRESH      = 0xE7,    
	K_WEBSTOP         = 0xE8,    
	K_WEBFORWARD      = 0xE9,    
	K_WEBBACK         = 0xEA,    
	K_MYCOMPUTER      = 0xEB,    
	K_MAIL            = 0xEC,    
	K_MEDIASELECT     = 0xED,    
};	// enum KEY_TYPE

//===================================================================================//
//!< マウスデバイス関連 
//===================================================================================//

/** マウスのボタンの種類 */
enum MOUSE_BTN_TYPE
{
	MOUSE_LEFT,		//!< 左ボタン
	MOUSE_RIGHT,	//!< 右ボタン
	MOUSE_CENTER,	//!< 真ん中ボタン
	MOUSE_BTN_MAX,
};	// enum MOUSE_BTN_TYPE

/** マウスホイールの状態 */
enum MOUSE_WHEEL_STATE
{
	WHEEL_NONE	= 0,		//!< 回転していない
	WHEEL_UP	= 1,		//!< 奥に回転
	WHEEL_DOWN	= -1,		//!< 手前に回転
};	// enum MOUSE_WHEEL_STATE

//===================================================================================//
//!< XBOXコントローラー関連
//===================================================================================//

/** XBOXコントローラーのボタンアクションの列挙 */
enum XIDEVICE_ACTION_TYPE
{
	XIDEVICE_DPAD_UP           ,		//<! 十字キーの上
	XIDEVICE_DPAD_DOWN         ,		//<! 十字キーの下
	XIDEVICE_DPAD_LEFT         ,		//<! 十字キーの左
	XIDEVICE_DPAD_RIGHT        ,		//<! 十字キーの右
	XIDEVICE_START             ,		//<! スタートボタン
	XIDEVICE_BACK              ,		//<! バックボタン
	XIDEVICE_LEFT_THUMB        ,		//<! 左スティックのボタン
	XIDEVICE_RIGHT_THUMB       ,		//<! 右スティックのボタン
	XIDEVICE_LEFT_SHOULDER     ,		//<! LBボタン
	XIDEVICE_RIGHT_SHOULDER    ,		//<! RBボタン
	XIDEVICE_A                 ,		//<! Aボタン
	XIDEVICE_B                 ,		//<! Bボタン
	XIDEVICE_X                 ,		//<! Xボタン
	XIDEVICE_Y                 ,		//<! Yボタン
	XIDEVICE_BTN_MAX		   ,		//<! ボタンの総数 /** @attention ここのIDは仕様しないこと ---------------- */
	XIDEVICE_LTRIGGER		   ,		//<! 左のトリガー
	XIDEVICE_RTRIGGER		   ,		//<! 右のトリガー
	XIDEVICE_LSTICK_UP		   ,		//<! 左スティックの上判定
	XIDEVICE_LSTICK_DOWN	   ,		//<! 左スティックの下判定
	XIDEVICE_LSTICK_RIGHT	   ,		//<! 左スティックの右判定
	XIDEVICE_LSTICK_LEFT	   ,		//<! 左スティックの左判定
	XIDEVICE_RSTICK_UP		   ,		//<! 右スティックの上判定
	XIDEVICE_RSTICK_DOWN	   ,		//<! 右スティックの下判定
	XIDEVICE_RSTICK_RIGHT	   ,		//<! 右スティックの右判定
	XIDEVICE_RSTICK_LEFT	   ,		//<! 右スティックの左判定
	XIDEVICE_ID_MAX		   ,		//<! IDの数
};	// enum XIDEVICE_ACTION_TYPE

}	// namespace sl

#endif	// SL_INPUT_DEVICE_DECLARATION_H


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
