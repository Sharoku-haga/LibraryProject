//==================================================================================================================================//
//!< @file		slDIKeyboard.cpp
//!< @brief		sl::DIKeyboardクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/07	更新履歴：2017/10/08
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <algorithm>
#include "slDIKeyboard.h"
#include "../../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DIKeyboard::DIKeyboard(LPDIRECTINPUTDEVICE8 pKeyDevice)
	: m_pDIKeyDevice(pKeyDevice)
{
	for(int i = 0; i < m_KeyTypeCount; ++i)
	{
		m_CurrentKeyState[i]	= OFF;
		m_OldKeyState[i]		= OFF;
	} 
}

void DIKeyboard::RegisterUsingKey(KEY_TYPE key)
{
	if(m_UsingKey.size() != 0)
	{
		// 引数のキーがすでに登録されているか確認し、
		// 登録されているなら即returnする
		auto result = std::find(m_UsingKey.begin(), m_UsingKey.end(), key);
		if(result != m_UsingKey.end())
		{
			return;
		}
	}

	m_UsingKey.push_back(key);
}

void DIKeyboard::UpdateState()
{
	// デバイスからキーの状態を取得する
	HRESULT hr = m_pDIKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pDIKeyDevice->GetDeviceState(sizeof(m_DIKeys), &m_DIKeys);
	}

	// 使用するキー全ての状態を更新する
	for( auto& key : m_UsingKey)
	{
		UpdateKeyState(key);
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void DIKeyboard::UpdateKeyState(KEY_TYPE key)
{
	if(m_DIKeys[key] & 0x80)
	{
		if(m_OldKeyState[key] == OFF)
		{
			m_CurrentKeyState[key] = PUSH;
		}
		else
		{
			m_CurrentKeyState[key] = ON;
		}
		m_OldKeyState[key] = ON;
	}
	else
	{
		if(m_OldKeyState[key] == ON)
		{
			m_CurrentKeyState[key] = RELEASE;
		}
		else
		{
			m_CurrentKeyState[key] = OFF;
		}
		m_OldKeyState[key] = OFF;
	}
}

}
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
