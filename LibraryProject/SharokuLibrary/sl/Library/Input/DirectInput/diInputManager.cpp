//==================================================================================================================================//
//!< @file		diInputManager.h
//!< @brief		di::InputManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "diInputManager.h"
#include "diKeyDevice.h"
#include "diGamePad.h"
#include "../../../slBuild.h"
#include "../../../Common/slTemplate.h"
#include "../../../Common/slDefine.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace di
{

/* Public Functions ------------------------------------------------------------------------------------------- */

InputManager::InputManager(void)
	: m_pDInput8(NULL)
	, m_hWnd(NULL)
	, m_pKeyDevice(nullptr)
	, m_pGamePad(nullptr)
{}

InputManager::~InputManager(void)
{
	DeleteSafely(m_pGamePad);
	DeleteSafely(m_pKeyDevice);
	ReleaseSafely(m_pDInput8);
}

bool InputManager::Initialize(HWND hWnd)
{
	//	DirectInput オブジェクトの作成
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),
								DIRECTINPUT_VERSION, 
								IID_IDirectInput8, 
								reinterpret_cast<void**>(&m_pDInput8), 
								NULL)))
	{
		MessageBox(0, "DirectInputオブジェクト生成に失敗しました。", NULL, MB_OK);
		return false;
	}

#ifdef USING_KEY_DEVICE
	m_pKeyDevice = new KeyDevice();

	if(RESULT_FAILED(m_pKeyDevice->Initialize(m_pDInput8, hWnd)))
	{
		DeleteSafely(m_pKeyDevice);
		MessageBox(0, "キーボードデバイスの初期化に失敗しました。", NULL, MB_OK);
		return false;
	}

#endif// USING_KEY_DEVICE

#ifdef USING_DI_GAMEPAD
	m_pGamePad = new GamePad();
	m_pGamePad->Initialize(m_pDInput8, hWnd);
#endif// USING_KEY_DEVICE

	return true;
}

void InputManager::Update(void)
{

#ifdef USING_KEY_DEVICE
	m_pKeyDevice->Update();
#endif// USING_KEY_DEVICE

#ifdef USING_DI_GAMEPAD
	m_pGamePad->Update();
#endif// USING_KEY_DEVICE

}

DEVICE_STATE InputManager::CheckKey(int keyID)
{
	return m_pKeyDevice->CheckKey(keyID);
}

}	// namespace di 
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
