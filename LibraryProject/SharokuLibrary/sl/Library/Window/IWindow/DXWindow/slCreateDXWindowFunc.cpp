//==================================================================================================================================//
//!< @file		slCreateDXWindowFunc.cpp
//!< @brief		DXWinodwクラスを生成する関数の実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/06	更新履歴：2017/09/23
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXWindow.h"
#include "slCreateDXWindowFunc.h"
#include "../../../../slBuild.h"
#include "../../../Debugger/slDebugDefine.h"

namespace sl
{

/*  Global Function ------------------------------------------------------------------------------------------- */

// ウィンドウプロシージャ関数
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
		break;

	case WM_KEYDOWN:
		switch(static_cast<char>(wParam))
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

#ifdef ADJUST_CLIENT_SIZE

/** 
* クライアントサイズを指定されたサイズに調整する関数
* @param[in] hWnd		調整したいウィンドウのハンドル
* @param[in] widthSize	調整したい横のサイズ
* @param[in] heightSize	調整したい縦のサイズ
*/
void AjustClientSize(HWND hWnd, int widthSize, int heightSize)
{
	// ウィンドウサイズとクライアントサイズを求める
	RECT widowRect;
	GetWindowRect(hWnd, &widowRect);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	// ウィンドウサイズとクライアントサイズの差からウィンドウの枠の長さを求める
	int winFlameWidth  = static_cast<int>((widowRect.right - widowRect.left) - (clientRect.right - clientRect.left));
	int winFlameHeight = static_cast<int>((widowRect.bottom - widowRect.top) - (clientRect.bottom - clientRect.top));

	// ウィンドウの幅を再設定する
	SetWindowPos(hWnd, HWND_TOP, 0, 0, (widthSize + winFlameWidth), (heightSize + (widowRect.bottom - clientRect.bottom)), SWP_NOMOVE);
}

#endif	// ADJUST_CLIENT_SIZE

/* Function --------------------------------------------------------------------------------------------------- */

UniquePtr<DXWindow> CreateDXWindow(const WindowCreationData& rData, HICON  hIcon, HWND hWndParent)
{
	// ウィンドウ情報の設定
	WNDCLASSEX  WndClass;
	WndClass.cbSize				= sizeof(WndClass);
	WndClass.style				= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc		= WndProc;
	WndClass.cbClsExtra			= 0;
	WndClass.cbWndExtra			= 0;
	WndClass.hInstance			= GetModuleHandle(NULL);
	WndClass.hIcon				= hIcon;
	WndClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName		= NULL;
	WndClass.lpszClassName		= rData.m_pTitle;
	WndClass.hIconSm			= hIcon;
	RegisterClassEx(&WndClass);

	// ウィンドウ作成
	HWND hWnd = CreateWindow(
		rData.m_pTitle,
		rData.m_pTitle,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		rData.m_Width,
		rData.m_Height,
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	if(hWnd == NULL)
	{
		MessageBox(0, "ウィンドウ生成に失敗しました。", NULL, MB_OK);
		slAssertCheckExpression((hWnd != NULL));
	}

	SetProcessDPIAware();					// WindowsにDPIAwareであることを示す(不適切なサイズやフォントが使用されるのを防ぐ)

#ifdef ADJUST_CLIENT_SIZE

	AjustClientSize(hWnd, rData.m_Width, rData.m_Height);

#endif	// ADJUST_CLIENT_SIZE

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetWindowText(hWnd, rData.m_pTitle);

	return MakeUniquePtr<DXWindow>(hWnd);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
