//==================================================================================================================================//
//!< @file		slDIDeviceManager.cpp
//!< @brief		sl::DIDeviceManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/08
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
	, m_pKeyDevice(NULL)
	, m_pMouseDevice(NULL)
{}

DIDeviceManager::~DIDeviceManager()
{
	SafeReleaseDX(m_pMouseDevice);
	SafeReleaseDX(m_pKeyDevice);
	SafeReleaseDX(m_pDInput8);
}

bool DIDeviceManager::Initialize(const WindowHandle& rHandle)
{
	m_WinHandle = rHandle;

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

bool DIDeviceManager::CreateDIKeyDevice()
{
	//	キーボードの初期化
	if(FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard
										, &m_pKeyDevice
										, NULL)))
	{
		slOutputDebugString("DirectInputキーボード初期化に失敗しました");
		return false;
	}

	//	データフォーマット
	if(FAILED(m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		slOutputDebugString("キーボードデバイスのデータフォーマットに失敗しました。");
		SafeReleaseDX(m_pKeyDevice);
		return false;
	}

	//	協調レベル
	if(FAILED(m_pKeyDevice->SetCooperativeLevel(static_cast<HWND>(m_WinHandle.m_pAdress)
											, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		slOutputDebugString("キーボードデバイスの協調レベル設定に失敗しました。");
		SafeReleaseDX(m_pKeyDevice);
		return false;
	}

	// アクセス許可
	m_pKeyDevice->Acquire();
	return true;
}

bool DIDeviceManager::CreateDIMouseDevice()
{
	if (FAILED(m_pDInput8->CreateDevice(GUID_SysMouse
										, &m_pMouseDevice, NULL)))
	{
		slOutputDebugString("DirectInputマウスの初期化に失敗しました。");
		return false;
	}

	if(FAILED(m_pMouseDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		slOutputDebugString("マウスデバイスのデータフォーマットに失敗しました。");
		SafeReleaseDX(m_pMouseDevice);
		return false;
	}

	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diprop;
	diprop.diph.dwSize			= sizeof(diprop);					// 包含する構造体のサイズ
	diprop.diph.dwHeaderSize	= sizeof(diprop.diph);				// DIPROPHEADER 構造体のサイズ
	diprop.diph.dwObj			= 0;								// アクセスするプロパティが属するオブジェクト
	diprop.diph.dwHow			= DIPH_DEVICE;						// dwObj メンバの解釈方法を指定する値
	diprop.dwData				= 1000;								// 設定または取得されるプロパティ値
	//	diprop.dwData		= DIPROPAXISMODE_ABS;	// 絶対値モードの場合
	if (FAILED(m_pMouseDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph)))
	{
		slOutputDebugString("マウスデバイスの軸モードの設定に失敗");
		SafeReleaseDX(m_pMouseDevice);
		return false;
	}

	//	協調レベル
	if (FAILED(m_pMouseDevice->SetCooperativeLevel(static_cast<HWND>(m_WinHandle.m_pAdress)
												, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		slOutputDebugString("マウスデバイスの協調レベルの設定に失敗しました。");
		SafeReleaseDX(m_pMouseDevice);
		return false;
	}

	// アクセス許可
	m_pMouseDevice->Acquire();

	return true;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
