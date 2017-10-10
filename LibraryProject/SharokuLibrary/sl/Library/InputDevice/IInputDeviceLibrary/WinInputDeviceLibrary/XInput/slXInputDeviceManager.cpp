//==================================================================================================================================//
//!< @file		slXInputDeviceManager.cpp
//!< @brief		sl::XInputDeviceManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/07	更新履歴：2017/10/11
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slXInputDeviceManager.h"
#include "../../../../Utility/slDefine.h"

namespace sl
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

constexpr BYTE	TriggerThreshold	= 240;				// トリガーのしきい値
constexpr SHORT	StickThreshold		= 16383;			// スティックのしきい値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

XInputDeviceManager::XInputDeviceManager()
{
	// デバイスを1つ作成する
	AddDevice();
}

bool XInputDeviceManager::AddDevice()
{
	if(m_Devices.size() == m_DeviceCountMaxVal)
	{
		return false;
	}

	// デバイス追加
	m_Devices.emplace_back();

	std::vector<INPUT_DEVICE_STATE> states;
	states.resize(XIDEVICE_ID_MAX);
	for(auto& state : states)
	{
		state = OFF;
	}

	m_CurrentDeviceState.push_back(states);
	m_OldDeviceState.push_back(states);

	return true;
}

void XInputDeviceManager::UpdateState()
{
	for(unsigned int i = 0; i < m_Devices.size(); ++i)
	{
		// デバイスが接続しているかを確認する
		DWORD dwResult = XInputGetState(static_cast<DWORD>(i), &m_Devices[i].m_XIState);

		if(dwResult == ERROR_SUCCESS)
		{
			m_Devices[i].m_IsConnected = true;
		}
		else
		{
			m_Devices[i].m_IsConnected = false;
		}

		// ボタンの状態を更新する
		UpdateButtonState(i);

		// ボタン以外の部位を更新する
		UpdatePartState(i);
	}
}

bool XInputDeviceManager::CheckActionState(XIDEVICE_ACTION_TYPE actionType, INPUT_DEVICE_STATE checkState, unsigned int deviceNum)
{
	if(RESULT_FALSE(m_Devices[deviceNum].m_IsConnected)
		|| deviceNum > m_Devices.size())
	{
		return false;
	}

	if(m_CurrentDeviceState[deviceNum][actionType] == checkState)
	{
		return true;
	}

	return false;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void XInputDeviceManager::UpdateButtonState(int deviceNum)
{
	for(int i = 0; i < XIDEVICE_BTN_MAX; ++i)
	{
		// チェックしたい番号を設定する
		WORD checkNum = 0x00000001;
		if(i < sl::XIDEVICE_A)
		{
			checkNum = checkNum << i;
		}
		else if(i < sl::XIDEVICE_X)
		{
			checkNum = 0x1000;
			checkNum += (0x1000 * (i - sl::XIDEVICE_A));
		}
		else
		{
			checkNum = 0x4000;
			checkNum += (0x4000 * (i - sl::XIDEVICE_X));
		}
		
		// 更新したデバイスデータをチェックし、状態を更新する
		bool checkResult = false;
		
		if(m_Devices[deviceNum].m_XIState.Gamepad.wButtons & checkNum)
		{
			checkResult = true;
		}

		UpdateState(deviceNum, i, checkResult);
	}
}

void XInputDeviceManager::UpdatePartState(int deviceNum)
{

	for(int i = XIDEVICE_LTRIGGER; i < XIDEVICE_ID_MAX; ++i)
	{
		// それぞれ設定したしきい値をもとに更新したデバイスデータをチェックする
		bool checkResult = false;
		switch(i)
		{

		case XIDEVICE_LTRIGGER:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.bLeftTrigger >= TriggerThreshold;
			break;

		case XIDEVICE_RTRIGGER:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.bRightTrigger >= TriggerThreshold;
			break;

		case XIDEVICE_LSTICK_UP:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbLY > StickThreshold;
			break;

		case XIDEVICE_LSTICK_DOWN:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbLY < -StickThreshold;
			break;

		case XIDEVICE_LSTICK_RIGHT:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbLX > StickThreshold;
			break;

		case XIDEVICE_LSTICK_LEFT:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbLX < -StickThreshold;
			break;

		case XIDEVICE_RSTICK_UP:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbRY > StickThreshold;
			break;

		case XIDEVICE_RSTICK_DOWN:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbRY < -StickThreshold;
			break;

		case XIDEVICE_RSTICK_RIGHT:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbRX > StickThreshold;
			break;

		case XIDEVICE_RSTICK_LEFT:
			checkResult = m_Devices[deviceNum].m_XIState.Gamepad.sThumbRX < -StickThreshold;
			break;

		default:
			// do nothing
			break;
		}

		// デバイスデータを更新する
		UpdateState(deviceNum, i, checkResult);
	}
}

void XInputDeviceManager::UpdateState(int deviceNum, int actionTypeID, bool isUsed)
{
	if(isUsed)
	{
		if(m_OldDeviceState[deviceNum][actionTypeID] == OFF)
		{
			m_CurrentDeviceState[deviceNum][actionTypeID] = PUSH;
		}
		else
		{
			m_CurrentDeviceState[deviceNum][actionTypeID] = ON;
		}
		m_OldDeviceState[deviceNum][actionTypeID] = ON;
	}
	else
	{
		if(m_OldDeviceState[deviceNum][actionTypeID] == ON)
		{
			m_CurrentDeviceState[deviceNum][actionTypeID] = RELEASE;
		}
		else
		{
			m_CurrentDeviceState[deviceNum][actionTypeID] = OFF;
		}
		m_OldDeviceState[deviceNum][actionTypeID] = OFF;
	}
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
