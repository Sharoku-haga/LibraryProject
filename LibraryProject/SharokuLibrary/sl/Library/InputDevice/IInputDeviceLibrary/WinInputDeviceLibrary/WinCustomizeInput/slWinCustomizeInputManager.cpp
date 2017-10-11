//==================================================================================================================================//
//!< @file		slWinCustomizeInputManager.cpp
//!< @brief		sl::WinCustomizeInputManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/11	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <algorithm>
#include "../../../../Debugger/slDebugDefine.h"
#include "../DirectInput/slDIKeyboard.h"
#include "../DirectInput/slDIMouse.h"
#include "../XInput/slXInputDeviceManager.h"
#include "slWinCustomizeInputManager.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

WinCustomizeInputManager::WinCustomizeInputManager()
	: m_pKeyboard(NULL)
	, m_pMouse(NULL)
	, m_pXInputDeviceManager(NULL)
{}

void WinCustomizeInputManager::RegisterCustomizeKey(int id, KEY_TYPE keyType)
{
	slAssertCheckExpression(m_pKeyboard != nullptr);
	RegisterCustomizeDevice(id, KEYBOARD);
	m_CustomizeKey[id].push_back(keyType);
}

void WinCustomizeInputManager::RegisterCustomizeMouseButton(int id, MOUSE_BTN_TYPE mouseBtn)
{
	slAssertCheckExpression(m_pMouse != nullptr);
	RegisterCustomizeDevice(id, MOUSE);
	m_CustomizeMouseButton[id].push_back(mouseBtn);
}

void WinCustomizeInputManager::RegisterCustomizeXInputAction(int id, XIDEVICE_ACTION_TYPE actionType)
{
	slAssertCheckExpression(m_pXInputDeviceManager != nullptr);
	RegisterCustomizeDevice(id, XINPUT_DEVICE);
	m_CustomizeXInputAction[id].push_back(actionType);
}

bool WinCustomizeInputManager::CheckCustomizeInputState(int id, INPUT_DEVICE_STATE checkState, int deviceNum)
{
	bool checkResult = false;
	
	for(auto& deviceType : m_CustomizeDevice[id])
	{
		switch(deviceType)
		{
		case KEYBOARD:
			for(auto& customizeKey : m_CustomizeKey[id])
			{
				checkResult = m_pKeyboard->CheckKeyState(customizeKey, checkState);

				if(checkResult)
				{	// 指定した状態ならループを抜ける
					break;
				}
			}
			break;

		case MOUSE:
			for(auto& customizeMouseBtn : m_CustomizeMouseButton[id])
			{
				checkResult = m_pMouse->CheckButtonState(customizeMouseBtn, checkState);

				if(checkResult)
				{	// 指定した状態ならループを抜ける
					break;
				}
			}
			break;

		case XINPUT_DEVICE:
			for(auto& customizeXInputAction : m_CustomizeXInputAction[id])
			{
				checkResult = m_pXInputDeviceManager->CheckActionState(customizeXInputAction, checkState);
				if(checkResult)
				{	// 指定した状態ならループを抜ける
					break;
				}
			}
			break;

		default:
			// do nothing
			break;
		}

		if(checkResult)
		{	// 指定した状態ならループを抜ける
			break;
		}
	}

	return checkResult;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void WinCustomizeInputManager::RegisterCustomizeDevice(int id, INPUT_DEVICE_TYPE deviceType)
{
	if(m_CustomizeDevice[id].size() != 0)
	{
		auto result = std::find( m_CustomizeDevice[id].begin(),  m_CustomizeDevice[id].end(), deviceType);
		if(result != m_CustomizeDevice[id].end())
		{
			return;
		}
	}
		
	m_CustomizeDevice[id].push_back(deviceType);
}


}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
