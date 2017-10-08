//==================================================================================================================================//
//!< @file		slDIDeviceManager.cpp
//!< @brief		sl::DIDeviceManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <windows.h>
#include "slDIDeviceManager.h"
#include "../../../../Debugger/slDebugFunction.h"
#include "../../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DIDeviceManager::DIDeviceManager()
	: m_pDInput8(NULL)
{}

DIDeviceManager::~DIDeviceManager()
{
	SafeReleaseDX(m_pDInput8);
}

bool DIDeviceManager::Initialize(const WindowHandle& rHandle)
{
	m_Handle = rHandle;

	//	DirectInput オブジェクトの生成
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),
								DIRECTINPUT_VERSION, 
								IID_IDirectInput8, 
								reinterpret_cast<void**>(&m_pDInput8), 
								NULL)))
	{
		slOutputDebugString("DirectInput オブジェクトの生成に失敗しました");
		return false;
	}
	return true;
}

LPDIRECTINPUTDEVICE8	DIDeviceManager::CreateDIKeyDevice()
{
	LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;

	//	キーボードの初期化
	if(FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard
										, &pKeyDevice
										, NULL)))
	{
		slOutputDebugString("DirectInputキーボード初期化に失敗しました");
		return pKeyDevice;
	}

	//	データフォーマット
	if(FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		slOutputDebugString("キーボードデバイスのデータフォーマットに失敗しました。");
		SafeReleaseDX(pKeyDevice);
		return pKeyDevice;
	}

	//	協調レベル
	if(FAILED(pKeyDevice->SetCooperativeLevel(static_cast<HWND>(m_Handle.m_pAdress)
											, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		slOutputDebugString("キーボードデバイスの協調レベル設定に失敗しました。");
		SafeReleaseDX(pKeyDevice);
		return pKeyDevice;
	}

	// アクセス許可
	pKeyDevice->Acquire();
	return pKeyDevice;
}

LPDIRECTINPUTDEVICE8	DIDeviceManager::CreateDIMouseDevice()
{
	LPDIRECTINPUTDEVICE8 pMouseDevice = NULL;
	if (FAILED(m_pDInput8->CreateDevice(GUID_SysMouse
										, &pMouseDevice, NULL)))
	{
		slOutputDebugString("DirectInputマウスの初期化に失敗しました。");
		return pMouseDevice;
	}

	if(FAILED(pMouseDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		slOutputDebugString("マウスデバイスのデータフォーマットに失敗しました。");
		SafeReleaseDX(pMouseDevice);
		return pMouseDevice;
	}

	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diprop;
	diprop.diph.dwSize			= sizeof(diprop);					// 包含する構造体のサイズ
	diprop.diph.dwHeaderSize	= sizeof(diprop.diph);				// DIPROPHEADER 構造体のサイズ
	diprop.diph.dwObj			= 0;								// アクセスするプロパティが属するオブジェクト
	diprop.diph.dwHow			= DIPH_DEVICE;						// dwObj メンバの解釈方法を指定する値
	diprop.dwData				= 1000;								// 設定または取得されるプロパティ値
	//	diprop.dwData		= DIPROPAXISMODE_ABS;	// 絶対値モードの場合
	if (FAILED(pMouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph)))
	{
		slOutputDebugString("軸モードの設定に失敗");
		SafeReleaseDX(pMouseDevice);
		return pMouseDevice;
	}

	//	協調レベル
	if (FAILED(pMouseDevice->SetCooperativeLevel(static_cast<HWND>(m_Handle.m_pAdress)
												, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		slOutputDebugString("協調レベルの設定に失敗しました。");
		SafeReleaseDX(pMouseDevice);
		return pMouseDevice;
	}

	// アクセス許可
	pMouseDevice->Acquire();

	return pMouseDevice;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
