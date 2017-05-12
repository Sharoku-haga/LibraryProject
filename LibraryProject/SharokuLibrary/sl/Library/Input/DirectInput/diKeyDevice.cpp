//==================================================================================================================================//
//!< @file		diKeyDevice.cpp
//!< @brief		di::KeyDeviceクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "diKeyDevice.h"
#include "../../../Common/slInputEnum.h"
#include "../../../Common/slTemplate.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace di
{

/* StaticVariable --------------------------------------------------------------------------------------------- */

const int	KeyDevice::m_KeyStateNum;			

/* Public Functions ------------------------------------------------------------------------------------------- */

KeyDevice::KeyDevice(void)
	: m_pDInput8(NULL)
	, m_pKeyDevice(NULL)
{
	for(int i = 0; i < m_KeyStateNum; i++)
	{
		m_CurrentKeyState[i]	= OFF;
		m_OldKeyState[i]		= OFF;
	} 
}

KeyDevice::~KeyDevice(void)
{
	ReleaseSafely(m_pKeyDevice);
}

bool KeyDevice::Initialize(LPDIRECTINPUT8 pDInput8, HWND hWnd)
{
	m_pDInput8 = pDInput8;

	//	キーボードの初期化
	if(FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard,
										&m_pKeyDevice, NULL)))
	{
		MessageBox(0, "DirectInputキーボード初期化に失敗しました。", NULL, MB_OK);
		return false;
	}

	//	データフォーマット
	if(FAILED(m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(0, "キーボードデバイスのデータフォーマットに失敗しました。", NULL, MB_OK);
		return false;
	}

	//	協調レベル
	if(FAILED(m_pKeyDevice->SetCooperativeLevel(hWnd, 
												DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(0, "キーボードデバイスの協調レベル設定に失敗しました。", NULL, MB_OK);
		return false;
	}

	// アクセス許可
	m_pKeyDevice->Acquire();
	return true;
}

void KeyDevice::Update(void)
{
	HRESULT hr = m_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pKeyDevice->GetDeviceState(sizeof(m_DIKs), &m_DIKs);
	}
}

DEVICE_STATE KeyDevice::CheckKey(int keyID)
{
	CheckState(keyID);
	return m_CurrentKeyState[keyID];
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void KeyDevice::CheckState(int keyID)
{
	if(m_DIKs[keyID] & 0x80)
	{
		if(m_OldKeyState[keyID] == OFF)
		{
			m_CurrentKeyState[keyID] = PUSH;
		}
		else
		{
			m_CurrentKeyState[keyID] = ON;
		}
		m_OldKeyState[keyID] = ON;
	}
	else
	{
		if(m_OldKeyState[keyID] == ON)
		{
			m_CurrentKeyState[keyID] = RELEASE;
		}
		else
		{
			m_CurrentKeyState[keyID] = OFF;
		}
		m_OldKeyState[keyID] = OFF;
	}
}

}	// namespace di 
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
