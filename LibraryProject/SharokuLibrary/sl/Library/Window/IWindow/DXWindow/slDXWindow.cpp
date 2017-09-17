//==================================================================================================================================//
//!< @file		slDXWindow.cpp
//!< @brief		sl::DXWindowクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/05	更新履歴：2017/09/17
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXWindow.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXWindow::DXWindow(HWND hWnd)
	: m_hWnd(hWnd)
{
	ZeroMemory(&m_WinMsg, sizeof(m_WinMsg));
}

DXWindow::~DXWindow()
{
	if(m_hWnd != nullptr)
	{
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
	}
}

bool DXWindow::Update()
{
	if(m_WinMsg.message != WM_QUIT)
	{
		if(PeekMessage(&m_WinMsg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&m_WinMsg);
			DispatchMessage(&m_WinMsg);
		}

		return false;
	}

	m_hWnd = nullptr;
	return true;
}

WindowHandle DXWindow::GetWindowHandle() const
{
	return WindowHandle(m_hWnd);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
