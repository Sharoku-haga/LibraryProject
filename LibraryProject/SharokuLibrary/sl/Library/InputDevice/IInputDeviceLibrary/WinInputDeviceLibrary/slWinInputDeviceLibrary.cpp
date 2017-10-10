//==================================================================================================================================//
//!< @file		slWinInputDeviceLibrary.cpp
//!< @brief		sl::WinInputDeviceLibraryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/10
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../../../Utility/slTemplateFunction.h"
#include "../../../Debugger/slDebugDefine.h"
#include "DirectInput/slDIDeviceManager.h"
#include "DirectInput/slDIKeyboard.h"
#include "DirectInput/slDIMouse.h"
#include "XInput/slXInputDeviceManager.h"
#include "slWinInputDeviceLibrary.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

WinInputDeviceLibrary::WinInputDeviceLibrary()
	: IInputDeviceLibrary()
	, m_pDeviceManager(nullptr)
	, m_pKeyboard(nullptr)
	, m_pMouse(nullptr)
	, m_pXInputDeviceManager(nullptr)
{}

WinInputDeviceLibrary::~WinInputDeviceLibrary()
{
	SafeDelete(m_pXInputDeviceManager);
	SafeDelete(m_pMouse);
	SafeDelete(m_pKeyboard);
	SafeDelete(m_pDeviceManager);
}

bool WinInputDeviceLibrary::Initialize(const WindowHandle& rHandle)
{
	m_pDeviceManager = new DIDeviceManager();
	return m_pDeviceManager->Initialize(rHandle);
}

bool WinInputDeviceLibrary::CreateInputDevice(INPUT_DEVICE_TYPE deviceType)
{
	switch(deviceType)
	{
	case KEYBOARD:
		if(m_pKeyboard == nullptr)
		{
			m_pDeviceManager->CreateDIKeyDevice();
			m_pKeyboard = new DIKeyboard(m_pDeviceManager->GetKeyDevice());
			m_pIInputDevice.push_back(m_pKeyboard);
			return true;
		}
		break;

	case MOUSE:
		if(m_pMouse == nullptr)
		{
			m_pDeviceManager->CreateDIMouseDevice();
			m_pMouse = new DIMouse(m_pDeviceManager->GetMouseDevice()
									, m_pDeviceManager->GetMouseDevice());
			m_pIInputDevice.push_back(m_pMouse);
			return true;
		}
		break;

	case XINPUT_DEVICE:
		if(m_pXInputDeviceManager == nullptr)
		{
			m_pXInputDeviceManager = new XInputDeviceManager();
			m_pIInputDevice.push_back(m_pXInputDeviceManager);
			return true;
		}
		break;

	default: 
		// do nothing
		break;
	}

	return false;
}

void WinInputDeviceLibrary::UpdateInputDeviceState()
{
	for(auto& pIInputDevice : m_pIInputDevice)
	{
		pIInputDevice->UpdateState();
	}
}

void WinInputDeviceLibrary::RegisterUsingKey(KEY_TYPE key)
{
	slAssertCheckExpression(m_pKeyboard != nullptr);
	m_pKeyboard->RegisterUsingKey(key);
}

INPUT_DEVICE_STATE WinInputDeviceLibrary::CheckKeyState(KEY_TYPE key)
{
	slAssertCheckExpression(m_pKeyboard != nullptr);
	return m_pKeyboard->GetCurrentKeyState(key);
}

void WinInputDeviceLibrary::ShowMouseCursor(bool isVisible)
{
	slAssertCheckExpression(m_pMouse != nullptr);
	m_pMouse->ShowMouseCursor(isVisible);
}

INPUT_DEVICE_STATE WinInputDeviceLibrary::CheckMouseButtonState(MOUSE_BTN_TYPE button)
{
	slAssertCheckExpression(m_pMouse != nullptr);
	return m_pMouse->GetButtonState(button);
}

MOUSE_WHEEL_STATE WinInputDeviceLibrary::CheckMouseWheelState()
{
	slAssertCheckExpression(m_pMouse != nullptr);
	return m_pMouse->GetWheelState();
}

const long_Point&	WinInputDeviceLibrary::GetMouseCursorPos()
{
	slAssertCheckExpression(m_pMouse != nullptr);
	return m_pMouse->GetMouseCursorPos();
}

void WinInputDeviceLibrary::SetMouseCursorPos(const int_Point& rPos)
{
	slAssertCheckExpression(m_pMouse != nullptr);
	m_pMouse->SetMouseCursorPos(rPos);
}

bool WinInputDeviceLibrary::AddXIputDevice()
{
	slAssertCheckExpression(m_pXInputDeviceManager != nullptr);
	return m_pXInputDeviceManager->AddDevice();
}

int WinInputDeviceLibrary::GetXInputDeviceCount()
{
	slAssertCheckExpression(m_pXInputDeviceManager != nullptr);
	return m_pXInputDeviceManager->GetDeviceCount();
}

INPUT_DEVICE_STATE WinInputDeviceLibrary::CheckXInputAction(XIDEVICE_ACTION_TYPE actionType)
{
	slAssertCheckExpression(m_pXInputDeviceManager != nullptr);
	return m_pXInputDeviceManager->GetDeviceState(actionType);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
