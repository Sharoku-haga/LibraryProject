//==================================================================================================================================//
//!< @file		slDIMouse.cpp		
//!< @brief		sl::DIMouseクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/07	更新履歴：2017/10/11
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDIMouse.h"

/* Public Functions ------------------------------------------------------------------------------------------- */

namespace sl
{

DIMouse::DIMouse(LPDIRECTINPUTDEVICE8 pMouseDevice, const WindowHandle& rHandle)
	: m_pMouseDevice(pMouseDevice)
	, m_WinHandle(rHandle)
	, m_WheelState(MOUSE_WHEEL_STATE::WHEEL_NONE)
{
	for(int i = 0; i < MOUSE_BTN_TYPE::MOUSE_BTN_MAX; ++i)
	{
		m_CurrentBTNState[i]	= OFF;
		m_OldBTNState[i]		= OFF;
	} 
}

void DIMouse::UpdateState()
{
	HRESULT hr = m_pMouseDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		 m_pMouseDevice->GetDeviceState(sizeof(m_DIMouseState), &m_DIMouseState);
	}

	// カーソル座標を更新
	UpdateMouseCursorPos();

	// マウスボタンの状態を更新
	UpdateButtonState();

	// ホイールの状態を更新
	UpdateWheelState();
}

bool DIMouse::CheckButtonState(MOUSE_BTN_TYPE btnType, INPUT_DEVICE_STATE checkState)
{
	if(m_CurrentBTNState[btnType] == checkState)
	{
		return true;
	}
	return false;
}

bool DIMouse::CheckWheelState(MOUSE_WHEEL_STATE checkState)
{
	if(m_WheelState == checkState)
	{
		return true;
	}
	return false;
}

void DIMouse::SetMouseCursorPos(const int_Point& rPos)
{
	// 現在アクティブであるウィンドウのハンドルを取得する
	HWND currentWHnd = GetActiveWindow();		

	// 現在アクティブなウィンドウと一致するならカーソルをセットする
	if(currentWHnd == static_cast<HWND>(m_WinHandle.m_pAdress))				
	{
		SetCursorPos(rPos.m_X, rPos.m_Y);
	}
}

void DIMouse::ShowMouseCursor(bool isVisible)
{
	ShowCursor(isVisible);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void DIMouse::UpdateMouseCursorPos()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(static_cast<HWND>(m_WinHandle.m_pAdress), &cursorPos);
	m_MouseCursorPos.m_X = cursorPos.x;
	m_MouseCursorPos.m_Y = cursorPos.y;
}

void DIMouse::UpdateButtonState()
{
	for(int i = 0; i < MOUSE_BTN_TYPE::MOUSE_BTN_MAX; ++i)
	{
		if(m_DIMouseState.rgbButtons[i])
		{
			if(m_OldBTNState[i] == OFF)
			{
				m_CurrentBTNState[i] = PUSH;
			}
			else
			{
				m_CurrentBTNState[i] = ON;
			}

			m_OldBTNState[i] = ON;
		}
		else
		{
			if(m_OldBTNState[i] == ON)
			{
				m_CurrentBTNState[i] = RELEASE;
			}
			else
			{
				m_CurrentBTNState[i] = OFF;
			}

			m_OldBTNState[i] = OFF;
		}
	}
}

void DIMouse::UpdateWheelState()
{
	if(m_DIMouseState.lZ > 0)
	{
		m_WheelState = WHEEL_UP;
		return;
	}
	else if(m_DIMouseState.lZ < 0)
	{
		m_WheelState = WHEEL_DOWN;
		return;
	}

	m_WheelState = WHEEL_NONE;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
