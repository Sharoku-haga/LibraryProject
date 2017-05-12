//==================================================================================================================================//
//!< @file		xiGamePad.h
//!< @brief		xi::GamePadクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "xiGamePad.h"
#include "../../../Common/slDefine.h"

namespace sl
{
namespace xi
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const BYTE	TriggerThreshold	= 240;				// トリガーのしきい値
const SHORT	StickThreshold		= 16383;			// スティックのしきい値

}

/* Static Variable -------------------------------------------------------------------------------------------- */

const int		GamePad::m_PadMaxVal;

/* Public Functions ------------------------------------------------------------------------------------------- */

GamePad::GamePad(void)
{
	for( int padNum = 0; padNum < m_PadMaxVal; ++padNum)
	{
		m_Pads[padNum].m_IsConnected = false;

		for(int i = 0; i < XIGAMEPAD_ID_MAX; ++i)
		{
			m_CurrentPadState[padNum][i] = OFF;
		}

		for(int i = 0; i < XIGAMEPAD_ID_MAX; ++i)
		{
			m_OldPadState[padNum][i] = OFF;
		}
	}
}

GamePad::~GamePad(void)
{}

void GamePad::Update(void)
{
    for( int i = 0; i < m_PadMaxVal; ++i )
    {
         DWORD dwResult = XInputGetState( static_cast<DWORD>(i), &m_Pads[i].m_State );

		if(dwResult == ERROR_SUCCESS)
		{
			m_Pads[i].m_IsConnected = true;
		}
		else
		{
			m_Pads[i].m_IsConnected = false;
		}
    }
}

DEVICE_STATE GamePad::CheckState(int actionID, int padNum)
{
	DEVICE_STATE result;
	if(RESULT_FAILED(m_Pads[padNum].m_IsConnected))
	{
		OutputDebugString("指定されたコントローラーは接続されていません\n");
		return (result = OFF);
	}

	if(actionID < XIGAMEPAD_BTN_MAX )
	{
		result = CheckButton(actionID, padNum);
	}
	else
	{
		result  = CheckPart(actionID, padNum);
	}

	return result;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

DEVICE_STATE GamePad::CheckButton(int actionID, int padNum)
{

	WORD checkNum = 0x00000001;
	if(actionID < sl::XIGAMEPAD_A)
	{
		checkNum = checkNum << actionID;
	}
	else if(actionID < sl::XIGAMEPAD_X)
	{
		checkNum = 0x1000;
		checkNum += (0x1000 * (actionID - sl::XIGAMEPAD_A));
	}
	else
	{
		checkNum = 0x4000;
		checkNum += (0x4000 * (actionID - sl::XIGAMEPAD_X));
	}
	

	if(m_Pads[padNum].m_State.Gamepad.wButtons & checkNum)
	{
		if(m_OldPadState[padNum][actionID] == OFF)
		{
			m_CurrentPadState[padNum][actionID] = PUSH;
		}
		else
		{
			m_CurrentPadState[padNum][actionID] = ON;
		}
		m_OldPadState[padNum][actionID] = ON;
	}
	else
	{
		if(m_OldPadState[padNum][actionID] == ON)
		{
			m_CurrentPadState[padNum][actionID] = RELEASE;
		}
		else
		{
			m_CurrentPadState[padNum][actionID] = OFF;
		}
		m_OldPadState[padNum][actionID] = OFF;
	}

	return m_CurrentPadState[padNum][actionID];
	
}

DEVICE_STATE GamePad::CheckPart(int actionID, int padNum)
{
	bool checkResult = false;
	switch(actionID)
	{

	case XIGAMEPAD_LTRIGGER		:
		checkResult = m_Pads[padNum].m_State.Gamepad.bLeftTrigger >= TriggerThreshold;
		break;

	case XIGAMEPAD_RTRIGGER		:  
		checkResult = m_Pads[padNum].m_State.Gamepad.bRightTrigger >= TriggerThreshold;
		break;

	case XIGAMEPAD_LSTICK_UP	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbLY > StickThreshold;
		break;

	case XIGAMEPAD_LSTICK_DOWN	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbLY < -StickThreshold;
		break;

	case XIGAMEPAD_LSTICK_RIGHT	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbLX > StickThreshold;
		break;

	case XIGAMEPAD_LSTICK_LEFT	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbLX < -StickThreshold;
		break;

	case XIGAMEPAD_RSTICK_UP	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbRY > StickThreshold;
		break;

	case XIGAMEPAD_RSTICK_DOWN	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbRY < -StickThreshold;
		break;

	case XIGAMEPAD_RSTICK_RIGHT	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbRX > StickThreshold;
		break;

	case XIGAMEPAD_RSTICK_LEFT	:
		checkResult = m_Pads[padNum].m_State.Gamepad.sThumbRX < -StickThreshold;
		break;

	default:
		// do nothing
		break;
	}

	if(checkResult)
	{
		if(m_OldPadState[padNum][actionID] == OFF)
		{
			m_CurrentPadState[padNum][actionID] = PUSH;
		}
		else
		{
			m_CurrentPadState[padNum][actionID] = ON;
		}
		m_OldPadState[padNum][actionID] = ON;
	}
	else
	{
		if(m_OldPadState[padNum][actionID] == ON)
		{
			m_CurrentPadState[padNum][actionID] = RELEASE;
		}
		else
		{
			m_CurrentPadState[padNum][actionID] = OFF;
		}
		m_OldPadState[padNum][actionID] = OFF;
	}

	return m_CurrentPadState[padNum][actionID];
}


}	// namespace xi
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
