//==================================================================================================================================//
//!< @file		slCustomizeInputManager.cpp
//!< @brief		sl::CustomizeInputManagerƒNƒ‰ƒXŽÀ‘•
//!< @author	T.Haga
//==================================================================================================================================//

#include "slCustomizeInputManager.h"
#include "DirectInput/diInputManager.h"
#include "DirectInput\diKeyDevice.h"
#include "XInput/xiGamePad.h"
#include "../../slBuild.h"

namespace sl
{

CustomizeInputManager::CustomizeInputManager(di::InputManager* pInputManager, xi::GamePad* pGamePad)
	: m_pKeyDevice(pInputManager->GetKeyDevice())
	, m_pXiGamePad(pGamePad)
{}

CustomizeInputManager::~CustomizeInputManager()
{}

void CustomizeInputManager::RegisterCustomizeType(int ID, HID_TYPE device, int inputType)
{
	CUSTOMIZE_INFO info = {device, inputType};
	m_CustomizeInfos[ID] = info;
}

DEVICE_STATE CustomizeInputManager::CheckState(int ID, int deviceNum)
{
	DEVICE_STATE state;
	CUSTOMIZE_INFO info = m_CustomizeInfos[ID];

	switch(info.m_DeviceType)
	{
	case KEYBOARD:
		state = m_pKeyDevice->CheckKey(info.m_InputType);
		break;

	case MOUSE:
		/** @todo ‚Ü‚¾ŽÀ‘•‚µ‚Ä‚¢‚È‚¢*/
		break;

	case GAMEPAD:
#ifdef USING_XI_GAMEPAD
		state = m_pXiGamePad->CheckState(info.m_InputType, deviceNum);
#endif
		break;

	default:
		// do nothing
		break;
	}

	return state;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
