//==================================================================================================================================//
//!< @file		diGamePad.cpp
//!< @brief		di::GamePadクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <windows.h>
#include <string>
#include "diGamePad.h"
#include "../../../Common/slTemplate.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace di
{

/* Struct ----------------------------------------------------------------------------------------------------- */

// EnumJoyCallbackに渡す構造体
struct ENUM_DEVICE_PARAM
{
	LPDIRECTINPUT8						m_pDInput8;					//!< DirectInputDevice
	LPDIRECTINPUTDEVICE8				m_pPadDevice;				//!< GamePadDevice
};

/* Prototype Declaration -------------------------------------------------------------------------------------- */

static BOOL CALLBACK EnumJoyCallback(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);
static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);

/* Public Functions ------------------------------------------------------------------------------------------- */

GamePad::GamePad(void)
	: m_pDInput8(NULL)
	, m_pPadDevice(NULL)
{}

GamePad::~GamePad(void)
{
	m_pPadDevice->Unacquire();
	ReleaseSafely(m_pPadDevice);
}

bool GamePad::Initialize(LPDIRECTINPUT8 pDInput8, HWND hWnd)
{
	m_pDInput8 = pDInput8;

	ENUM_DEVICE_PARAM param;
	param.m_pDInput8 = m_pDInput8;
	param.m_pPadDevice = NULL;

	if(FAILED(pDInput8->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoyCallback, reinterpret_cast<LPVOID>(&param), DIEDFL_ATTACHEDONLY )))
	{
		MessageBox(0, "ゲームパッドがみつかりませんでした。", NULL, MB_OK);
		return false;
	}
	else
	{
		int i = 0;
	}

	if(param.m_pPadDevice == NULL)
	{
		MessageBox(0, "ゲームパッドデバイスの生成に失敗しました。", NULL, MB_OK);
		return false;
	}
	else
	{
		m_pPadDevice = param.m_pPadDevice;
	}

	//	データフォーマット
	if(FAILED(m_pPadDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		MessageBox(0, "ゲームパッドデバイスのデータフォーマットに失敗しました。", NULL, MB_OK);
		return false;
	}

	// 軸モードを絶対値モードに設定
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize			= sizeof(diprop);
	diprop.diph.dwHeaderSize	= sizeof(diprop.diph);
	diprop.diph.dwObj			= 0;
	diprop.diph.dwHow			= DIPH_DEVICE;
	diprop.dwData				= DIPROPAXISMODE_ABS;
	if(FAILED(m_pPadDevice->SetProperty( DIPROP_AXISMODE, &diprop.diph )))
	{
		MessageBox(0, "軸モードの設定に失敗しました。", NULL, MB_OK);
		return false;
	}
	
	if(FAILED(m_pPadDevice->EnumObjects(EnumAxesCallback, reinterpret_cast<LPVOID>(m_pPadDevice), DIDFT_AXIS)))
	{
		MessageBox(NULL, "軸範囲の設定に失敗", "Direct Input Error", MB_OK);
		return false;
	}

	//バッファサイズの設定
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = 1000;
	m_pPadDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);

	//	協調レベル
	if(FAILED(m_pPadDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(0, "ゲームパッドデバイスの協調レベル設定に失敗しました。", NULL, MB_OK);
		return false;
	}

	m_pPadDevice->Acquire();

	return true;
}

void GamePad::Update(void)
{
	if(FAILED(m_pPadDevice->Poll()))
	{
		m_pPadDevice->Acquire();   
	}

	m_pPadDevice->GetDeviceState( sizeof( DIJOYSTATE ) , &m_DiJoyState );

	for(int i = 0; i < 32; ++i)
	{
		if(m_DiJoyState.rgbButtons[i])
		{
			std::string str = "ボタン" + std::to_string(i + 1) + "反応している";
			OutputDebugString(str.c_str());
		}
	}
}

void GamePad::CheckBtn()
{
	// 実装はまだ
}

/* Static CallBack Function ----------------------------------------------------------------------------------- */

static BOOL CALLBACK EnumJoyCallback(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef)
{
	ENUM_DEVICE_PARAM* param = reinterpret_cast<ENUM_DEVICE_PARAM*>(pvRef);

	if(FAILED(param->m_pDInput8->CreateDevice(ipddi->guidInstance , &(param->m_pPadDevice), NULL)))
	{
		 return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, LPVOID pvRef)
{
	LPDIRECTINPUTDEVICE8 pPadDevice = reinterpret_cast<LPDIRECTINPUTDEVICE8>(pvRef);

	// 軸の値の範囲設定
	// 十字キーを押していないときが0になるように
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize		= sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj		= pdidoi->dwType;
	diprg.diph.dwHow		= DIPH_BYOFFSET;
	diprg.lMin				= -1000;
	diprg.lMax				= 1000;
	
	if(FAILED(pPadDevice->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

}	// namespace di 
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
