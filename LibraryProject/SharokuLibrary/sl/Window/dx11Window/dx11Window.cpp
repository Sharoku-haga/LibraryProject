//==================================================================================================================================//
//!< @file		dx11Window.cpp
//!< @brief		dx11::Windowクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "dx11Window.h"
#include "../../slBuild.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace dx11
{

/* Global Function -------------------------------------------------------------------------------------------- */

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_KEYDOWN:
		switch(static_cast<char>(wParam))
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

/* Public Functions ------------------------------------------------------------------------------------------- */

Window::Window(void)
	: m_hWnd(NULL)
	, m_hWndParent(NULL)
{
	ZeroMemory(&m_WinMsg, sizeof(m_WinMsg));
}

Window::~Window(void)
{
	if(m_hWnd != NULL)
	{
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);						
	}
	else
	{
		// テスト用空処理. Finalizeでウィンドウを破棄しているか。そもそも生成していない場合にこの処理に入る
	}
}

bool Window::Initalize(t_char*  pWinTitle, int winWidth, int winHeight, HWND hWndParent)
{
	// ウィンドウ情報の設定
	WNDCLASSEX  WndClass;
	WndClass.cbSize				= sizeof(WndClass);
	WndClass.style				= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc		= WndProc;
	WndClass.cbClsExtra			= 0;
	WndClass.cbWndExtra			= 0;
	WndClass.hInstance			= GetModuleHandle(NULL);
	WndClass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName		= NULL;
	WndClass.lpszClassName		= pWinTitle;
	WndClass.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	// ウィンドウ作成
	m_hWnd = CreateWindow(
		pWinTitle,
		pWinTitle,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		winWidth,
		winHeight,
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	SetProcessDPIAware();					// WindowsにDPIAwareであることを示す(不適切なサイズやフォントが使用されるのを防ぐ)

	// クライアント領域を指定したサイズに調整する
#ifdef ADJUST_CLIENT_SIZE
	// ウィンドウサイズとクライアントサイズを求める
	RECT widow_rect;
	GetWindowRect(m_hWnd, &widow_rect);
	RECT client_rect;
	GetClientRect(m_hWnd, &client_rect);

	// ウィンドウサイズとクライアントサイズの差からウィンドウの枠の長さを求める
	int winFlameWidth  = static_cast<int>((widow_rect.right - widow_rect.left) - (client_rect.right - client_rect.left));
	int winFlameHeight = static_cast<int>((widow_rect.bottom - widow_rect.top) - (client_rect.bottom -= client_rect.top));

	// ウィンドウの幅を再設定する
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, (winWidth + winFlameWidth), (winHeight + (widow_rect.bottom - client_rect.bottom)), SWP_NOMOVE);
#endif	// ADJUST_CLIENT_SIZE

	if(m_hWnd == NULL)
	{
		MessageBox(0, "ウィンドウ生成に失敗しました。", NULL, MB_OK);
		return false;	
	}

	m_hWndParent = hWndParent;
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	SetWindowText(m_hWnd, pWinTitle);
	return true;
}

void Window::Finalize(void)
{
	if(m_hWnd != NULL)
	{
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);						// SendMessageの処理は同期
	}
	else
	{
		MessageBox(0, "破棄すべきウィンドウはありません。", NULL, MB_OK);
	}
}

HWND Window::GetHwnd(void) 
{ 
	return m_hWnd; 
}

bool Window::Update(void)
{
	if(m_WinMsg.message != WM_QUIT)
	{
		if(PeekMessage(&m_WinMsg, NULL, 0U, 0U, PM_REMOVE))
		{
			DispatchMessage(&m_WinMsg);
		}

		return false;
	}
	return true;
}

}	// namespace dx11
}	// namespace sl

	//==================================================================================================================================//
	// END OF FILE
	//==================================================================================================================================//
