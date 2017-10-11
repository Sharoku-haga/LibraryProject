//==================================================================================================================================//
//!< @file		slWinInputDeviceLibrary.cpp
//!< @brief		sl::WinInputDeviceLibraryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/06	更新履歴：2017/10/10
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../../../Utility/slTemplateFunction.h"
#include "../../../Debugger/slDebugDefine.h"
#include "XInput/slXInputDeviceManager.h"
#include "DirectInput/slDIDeviceManager.h"
#include "DirectInput/slDIKeyboard.h"
#include "DirectInput/slDIMouse.h"
#include "WinCustomizeInput/slWinCustomizeInputManager.h"
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
	, m_pCustomizeInputManager(nullptr)
{}

WinInputDeviceLibrary::~WinInputDeviceLibrary()
{
	SafeDelete(m_pXInputDeviceManager);
	SafeDelete(m_pMouse);
	SafeDelete(m_pKeyboard);
	SafeDelete(m_pDeviceManager);
	SafeDelete(m_pCustomizeInputManager);
}

bool WinInputDeviceLibrary::Initialize(const WindowHandle& rHandle)
{
	m_pCustomizeInputManager = new WinCustomizeInputManager();
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
			m_pCustomizeInputManager->SetDIKeyboard(m_pKeyboard);
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
			m_pCustomizeInputManager->SetDIMouse(m_pMouse);
			return true;
		}
		break;

	case XINPUT_DEVICE:
		if(m_pXInputDeviceManager == nullptr)
		{
			m_pXInputDeviceManager = new XInputDeviceManager();
			m_pIInputDevice.push_back(m_pXInputDeviceManager);
			m_pCustomizeInputManager->SetXInputDeviceManager(m_pXInputDeviceManager);
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

bool WinInputDeviceLibrary::CheckKeyState(KEY_TYPE key, INPUT_DEVICE_STATE checkState)
{
	slAssertCheckExpression(m_pKeyboard != nullptr);
	return m_pKeyboard->CheckKeyState(key, checkState);
}

void WinInputDeviceLibrary::ShowMouseCursor(bool isVisible)
{
	slAssertCheckExpression(m_pMouse != nullptr);
	m_pMouse->ShowMouseCursor(isVisible);
}

bool WinInputDeviceLibrary::CheckMouseButtonState(MOUSE_BTN_TYPE button, INPUT_DEVICE_STATE checkState)
{
	slAssertCheckExpression(m_pMouse != nullptr);
	return m_pMouse->CheckButtonState(button, checkState);
}

bool WinInputDeviceLibrary::CheckMouseWheelState(MOUSE_WHEEL_STATE checkState)
{
	slAssertCheckExpression(m_pMouse != nullptr);
	return m_pMouse->CheckWheelState(checkState);
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

bool WinInputDeviceLibrary::CheckXInputActionState(XIDEVICE_ACTION_TYPE actionType, INPUT_DEVICE_STATE checkState
							, unsigned int deviceNum)
{
	slAssertCheckExpression(m_pXInputDeviceManager != nullptr);
	return m_pXInputDeviceManager->CheckActionState(actionType, checkState, deviceNum);
}

void WinInputDeviceLibrary::RegisterCustomizeKey(int id, KEY_TYPE key)
{
	m_pCustomizeInputManager->RegisterCustomizeKey(id, key);
}

void WinInputDeviceLibrary::RegisterCustomizeMouseButton(int id, MOUSE_BTN_TYPE mouseBtn)
{
	m_pCustomizeInputManager->RegisterCustomizeMouseButton(id, mouseBtn);
}

void WinInputDeviceLibrary::RegisterCustomizeXInputAction(int id, XIDEVICE_ACTION_TYPE actionType)
{
	m_pCustomizeInputManager->RegisterCustomizeXInputAction(id, actionType);
}

bool WinInputDeviceLibrary::CheckCustomizeInputState(int id, INPUT_DEVICE_STATE checkState
										, int deviceNum)
{
	return m_pCustomizeInputManager->CheckCustomizeInputState(id, checkState, deviceNum);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
